# Claude Code + RAG System - Combined Reference

Two layers in one document. Part 1 is the plain-language walkthrough - read this first, or hand it to anyone who needs the mental model without the implementation detail. Part 2 is the full technical blueprint - the actual architecture, code, and verified research behind Part 1's simplified explanations.

**Quick navigation**

- Part 1: Plain-Language Overview - what the system is, how questions flow through it, what each folder/file does, in everyday language
- Part 2: Technical Reference - full architecture, MCP server code, RAG document-conversion research, verification against known practices, recommended skills/plugins

---

## Part 1: Plain-Language Overview

This is a plain-language version of `claude-rag-blueprint.md`. Same system, fewer assumptions about what you already know. Start here if the folder names and acronyms in the technical version aren't clicking yet.

---

### 1. The big picture, in one paragraph

You have a lot of specialized knowledge - mechanics docs, schematics, past code, V93K test programs, wafer data. You want an AI assistant that can actually use that knowledge instead of guessing. There are two separate systems for this, kept deliberately apart:

- **Lane 1 - Claude Code.** Runs on your computer, but the actual "thinking" happens on Anthropic's servers over the internet. Good for everyday work. Not for anything that legally can't leave your machine.
- **Lane 2 - your existing local setup.** Everything happens on your own computer, nothing goes anywhere. Slower, more setup, but the data never leaves your hands. This is for client work under NDA.

Think of Lane 1 like using a very smart consultant you call on the phone - convenient, capable, but you wouldn't read them your client's confidential blueprint over that phone. Lane 2 is like having an expert sitting in your locked office who never leaves the building.

---

### 2. How Claude Code organizes itself - the folder/file explainer

This is the part that looks like alphabet soup at first. Here's what everything actually does, in order of "you'll touch this most."

| File / folder | What it actually is | Plain-language analogy |
|---|---|---|
| `CLAUDE.md` | A text file you write. Claude reads it automatically at the start of every conversation, every time. | A sticky note on your desk that says "remember these things" - except a robot reads it before doing anything. |
| `.claude/agents/*.md` | Each file is a different "mode" or "personality" Claude can switch into - a specific job description with its own rules and allowed tools. | Job descriptions on a wall. "Wafer Analyst" has different duties than "QA Reviewer." Claude puts on the right hat for the task. |
| `.claude/skills/*/SKILL.md` | Short reference documents Claude only opens when relevant - not loaded all the time, just pulled out when needed. | A filing cabinet of cheat sheets. Claude doesn't carry every cheat sheet around, it grabs the right one off the shelf when the topic comes up. |
| `.claude/rules/*.md` | Like CLAUDE.md, but scoped to specific file types - only "active" when Claude is touching matching files. | A rule that's posted only on the door of one specific room, not the whole building. |
| `.claude/settings.json` | Configuration: what Claude is allowed to do without asking permission, automated checks that run after edits, etc. | The rulebook and the alarm system settings, in one file. |
| `.mcp.json` | A list of outside tools and databases Claude is allowed to connect to, and how to reach them. | A phone book - it doesn't contain the actual people, just their numbers and how to dial them. |
| `mcp_servers/*.py` | The actual small programs that do the connecting - to your ChromaDB, your wafer data, your schematic library. | The people the phone book's numbers actually ring through to. Claude asks a question, this program does the legwork and answers. |
| `MEMORY.md` (auto-generated) | Notes Claude writes about itself, automatically, after sessions - "this is how the build command works," "this is a pattern that keeps coming up." You don't write this one. | Claude's own personal notebook. You don't fill it in, it fills itself in as it learns things about your project. |

The single most important idea in this table: **CLAUDE.md and rules are things you write that Claude always reads. Skills are reference material Claude only opens when relevant. MCP servers are live connections to your actual data, not files Claude reads at all - they're more like Claude picking up a phone and asking a question.**

---

### 3. How a question actually travels through the system

Say you ask: *"what's the Cpk formula we used for bin1 IDDQ on lot X23?"*

```
You type the question
        |
        v
Claude checks: do I already know this, or do I need a tool?
        |
        v
Claude calls the "wafer-analysis" phone number (an MCP server)
        |
        v
That server searches your ChromaDB (your indexed documents and past code)
   and/or looks up the exact number in your spreadsheet-like data
        |
        v
The answer comes back to Claude
        |
        v
Claude writes you a real answer, using your actual data,
   not a guess based on general knowledge
```

Nothing in this chain happens automatically by magic - every step is a deliberate piece you set up once (the MCP server, the database, the CLAUDE.md instructions) and then it runs itself from then on.

---

### 4. What "RAG" actually means, without the acronym soup

RAG stands for Retrieval-Augmented Generation. Strip the jargon: **before answering, go look something up, then answer using what you found** - instead of answering purely from what the AI already "remembers" from training.

You already built this. Your `WEBRAG_INGEST.py` script reads your documents, breaks them into small pieces ("chunks"), and stores them in a searchable database (ChromaDB) along with a kind of fingerprint for each piece (an "embedding") that lets the computer find pieces that are *about the same topic*, even if they don't use the exact same words.

There are actually two different kinds of "looking something up," and mixing them up causes real problems:

- **Fuzzy lookup (vector/embedding search).** Good for "explain how X works" or "find code similar to this." The computer finds things that feel related.
- **Exact lookup (a database/spreadsheet query).** Good for "what's the actual yield number for lot X23." You don't want "something similar," you want the one correct number.

Using fuzzy search for things that need an exact answer is a real source of wrong answers - it's like asking a librarian to "find me a book kind of like this number" when what you actually wanted was a calculator.

---

### 5. The document-conversion problem, simply

Your PDFs (datasheets, the SI/PI textbook, schematics) were made for human eyes, not for a computer to read and understand. When you run a normal scanner-style text extraction ("OCR") over a page with a math formula or a data table, it often gets it badly wrong - not "slightly off," but actually scrambled into nonsense that looks confident and correct.

Real example from your own research:

```
What the OCR produced:    Lyie-via = 21 xhx n(B) pit (13-35)
What it actually was:     L = 2 × h × ln(B/D)   [a real, usable formula]
```

If that garbled version gets fed into your search database, two bad things happen: a human skimming it gets confused, and the AI trying to use it to answer a question gets actively misled, with no warning that anything went wrong. This is worse than just leaving that page out entirely.

**The fix:** for pages that are plain prose, cheap classic OCR works fine. For pages with formulas, tables, or diagrams, send those specific pages to a vision-capable AI model (one that can actually "look" at the image, not just read characters) and have it transcribe the page properly - formulas as real math notation, tables as real tables with rows and columns intact, images linked to their captions. You already started building exactly this two-step approach for the SI/PI textbook; it just hasn't been hooked up to your main ingestion script yet.

---

### 6. The "personas" explained - what subagents actually are

You already had this idea with your Engineer/Architect/QA setup. In Claude Code, the equivalent is a "subagent" - a text file describing a specific job, the tools that job is allowed to use, and the rules it follows.

```yaml
---
name: wafer-analyst
description: Use this one for wafer yield, STDF, and Cpk questions
---

Always write the simplest version of a script first. No fancy
error handling until asked. Always note assumptions at the top.
```

When you (or Claude on its own) decide a task fits the "wafer-analyst" job description, Claude switches into that mode - using that file's rules instead of its general defaults, and only the tools that job is allowed to touch.

One genuinely important nuance: this "switching into a mode" can happen two different ways, and they're not the same:

- **As a side-task ("subagent"):** Claude sends a quick, isolated question off to that persona, gets an answer back, and forgets the back-and-forth happened. Good for a one-off lookup.
- **As the whole conversation ("main agent"):** you tell Claude to *be* that persona for the entire session. Good for an extended back-and-forth, like working through a real analysis together, step by step, where it needs to remember what you discussed five minutes ago.

Picking the wrong one is a common mistake - using the quick, forgetful version for a task that actually needed ongoing memory of the conversation.

---

### 7. The full folder layout, annotated

This is the same tree from the technical document, with a plain-language comment on every line.

```
your-project/
├── CLAUDE.md                     # always-read instructions: build commands,
│                                  #   conventions, "remember these things"
├── .mcp.json                     # phone book - lists every outside data
│                                  #   connection Claude can use
├── .claude/
│   ├── agents/
│   │   ├── wafer-analyst.md      # job description #1
│   │   ├── lab-automation-engineer.md   # job description #2
│   │   └── qa-reviewer.md        # job description #3
│   ├── skills/
│   │   ├── v93k-conventions/SKILL.md      # cheat sheet, opened only when relevant
│   │   └── stdf-record-types/SKILL.md     # another cheat sheet
│   ├── rules/
│   │   ├── stdf-parsing.md       # instructions that only apply to STDF files
│   │   └── v93k-syntax.md        # instructions that only apply to V93K files
│   └── settings.json             # permissions + automated checks
├── mcp_servers/
│   ├── lab_automation_rag.py     # the actual program answering the
│   │                              #   "lab automation" phone line
│   ├── wafer_analysis_rag.py     # the program answering the
│   │                              #   "wafer analysis" phone line
│   ├── sipi_textbook_rag.py      # same idea, for the textbook
│   ├── schematics_rag.py         # same idea, for schematic images
│   └── wafer_data_sql.py         # NOT a search tool - this one does
│                                  #   exact lookups on real numbers
└── WEBRAG_INGEST.py               # your existing script that reads
                                    #   documents and fills the databases
                                    #   the mcp_servers above search
```

Your existing `WEBRAG_simple.py` (the one that loads a local AI model and chats) lives entirely outside this folder, on your local machine, doing Lane 2 work. It has nothing to do with Claude Code and doesn't need to.

---

### 8. Where this is weakest right now, simply put

Four honest gaps, easiest first:

1. **If you edit a document and re-process it, old leftover pieces don't get cleaned up.** The database just keeps growing with stale, outdated fragments mixed in with the current ones.
2. **Several of these "phone line" programs would each load their own copy of the AI model that turns text into a searchable fingerprint.** On a single graphics card, that's wasteful - better to have one shared copy they all use.
3. **The document-conversion fix described in section 5 isn't actually wired into your ingestion script yet.** The know-how exists, the script doesn't use it yet.
4. **Nothing currently checks whether the answers Claude finds are actually correct**, beyond a human reading them and noticing if something seems off. For test-pattern verification work specifically, this is worth fixing properly - a small file with known-correct answers that any generated code gets checked against before you trust it.

---

### 9. What to add later, simply put

A few official add-ons (called "plugins") that you install with one command, plus a few custom cheat sheets worth writing once you're using this regularly:

**Add-ons to install:**
- A Python helper that lets Claude understand your code more deeply (catches type errors automatically)
- A GitHub connector, so Claude can read your issues and pull requests directly
- A security-checking add-on that reviews every change Claude makes

**Cheat sheets worth writing yourself, once:**
- One that teaches Claude your document-conversion checklist from section 5, so it's followed automatically every time
- One that's just a template for the "phone line" programs in `mcp_servers/`, so building the fifth one is copy-paste instead of starting from scratch

---

### Quick reference: the three-sentence version

CLAUDE.md and rules are notes Claude always reads. Skills are cheat sheets Claude opens only when needed. MCP servers are live phone lines to your actual databases, called only when a question needs them - and whether that line does a "find something similar" search or a "get me the exact number" lookup is a choice you make per database, not something that's automatically right either way.


---

## Part 2: Technical Reference

System architecture for running your existing local AI pipeline alongside Claude Code, built directly from `WEBRAG_INGEST.py` and `WEBRAG_simple.py`.

> **DECISION:** two lanes, not one. Lane 1 (Claude Code, cloud reasoning) handles non-sensitive work. Lane 2 (your current local stack, unchanged) handles client IP and NDA-bound test programs. Nothing in Lane 2 ever becomes context for Lane 1. See `claude-code-vs-offline-stack` discussion for the data-handling rationale - consumer plans train on data by default, API/commercial plans don't, but everything still transits Anthropic's API.

---

### 1. System overview

```
┌──────────────────────────────────────────────────────────────────────┐
│                          YOUR WORKSTATION                              │
│                                                                          │
│  ┌────────────────────────┐         ┌──────────────────────────────┐  │
│  │  LANE 1 - Claude Code    │         │  LANE 2 - local stack         │  │
│  │  (cloud reasoning)        │         │  (unchanged, fully offline)   │  │
│  │                            │         │                                │  │
│  │  - your own conventions   │         │  - WEBRAG_simple.py            │  │
│  │  - public datasheets       │         │    (Qwen3.5 + Chroma, full     │  │
│  │  - generic patterns        │         │     local generation)          │  │
│  │  - non-NDA scripts         │         │  - client schematics, V93K     │  │
│  │                            │         │    test programs, anything     │  │
│  │  reasoning -> Anthropic API│         │    under NDA                   │  │
│  └────────────┬───────────────┘         │  - never touches Claude Code   │  │
│               │ MCP (stdio / http)       └──────────────────────────────┘  │
│               ▼                                                            │
│  ┌───────────────────────────────────────────────────────────────────┐   │
│  │             MCP RETRIEVAL SERVERS  (run on ai.local)                │   │
│  │                                                                       │   │
│  │  ┌────────────────┐ ┌─────────────────┐ ┌──────────────────────┐   │   │
│  │  │ lab-automation   │ │ wafer-analysis    │ │  sipi-textbook        │   │   │
│  │  │ (vector, Chroma) │ │ (vector, Chroma)  │ │  (vector + OCR pages) │   │   │
│  │  └────────────────┘ └─────────────────┘ └──────────────────────┘   │   │
│  │  ┌────────────────┐ ┌─────────────────┐                             │   │
│  │  │ wafer-data-sql   │ │ schematics-img    │                          │   │
│  │  │ (structured,     │ │ (vector + image    │                          │   │
│  │  │  pandas/parquet) │ │  paths, multimodal) │                          │   │
│  │  └────────────────┘ └─────────────────┘                             │   │
│  └───────────────────────────────────────────────────────────────────┘   │
└──────────────────────────────────────────────────────────────────────┘
```

Every box under "MCP retrieval servers" is the same underlying pattern: your `retrieve_context()` function from `WEBRAG_simple.py`, stripped of the Llama load, wrapped as a callable tool instead of a chat endpoint. Claude Code calls them the same way it calls Bash or Read - it doesn't know or care that one hits a vector DB and another runs a pandas query.

---

### 2. Component mapping

| Your stack | Claude Code primitive | What changes |
|---|---|---|
| `recent.md` preload | CLAUDE.md + auto memory | You stop writing it by hand; Claude writes `MEMORY.md` itself across sessions |
| 3-persona (Engineer/Architect/QA) | Subagents | Each persona's system prompt becomes a `.md` file with its own tools and model |
| `WEBRAG_INGEST.py` | Unchanged, runs standalone | Still your indexing step, no rewrite needed |
| `WEBRAG_simple.py` (retrieval half) | MCP server tool | `retrieve_context()` lifted out, Llama generation dropped |
| `WEBRAG_simple.py` (generation half) | Stays in Lane 2 | Full local chat app, untouched, for NDA work |
| `{{RAG_CONTEXT}}` injection | MCP tool call, on demand | Claude decides when to retrieve instead of every turn |
| Per-domain `SYSTEM_PROMPT` (wafer analyst, lab automation) | Subagent body | Near copy-paste into `.claude/agents/*.md` |
| JSON handoff between personas | Hooks + subagent chaining | Enforced deterministically instead of by convention |

---

### 3. Converting your two files

#### 3a. `WEBRAG_INGEST.py` - keep as is

No changes needed. This is your indexing pipeline and it runs the same way regardless of what queries the database afterward. Run it per corpus, pointed at a different `CHROMA_PATH`/`COLLECTION_NAME` each time, same as you do now for `lab_automation` vs `data_analysis`.

#### 3b. `WEBRAG_simple.py` - split in two

**Lane 1 piece (new): the MCP server.** Everything from `retrieve_context()` onward, minus the `Llama` load entirely - Claude Code's own model does the reasoning, so you don't need a local LLM in this path at all.

```python
# mcp_servers/wafer_analysis_rag.py
from mcp.server.fastmcp import FastMCP
import chromadb
from sentence_transformers import SentenceTransformer

CHROMA_PATH = "/home/alex/hugging_face_rag/chroma_db_data"
COLLECTION_NAME = "data_analysis"
EMBED_MODEL_NAME = "nomic-ai/nomic-embed-text-v1.5"

embed_model = SentenceTransformer(EMBED_MODEL_NAME)
chroma_client = chromadb.PersistentClient(path=CHROMA_PATH)
collection = chroma_client.get_or_create_collection(
    name=COLLECTION_NAME,
    metadata={"hnsw:space": "cosine"}
)

mcp = FastMCP(
    "wafer-analysis-rag",
    instructions="Search wafer yield/parametric analysis docs, STDF handling "
                 "patterns, and past Cpk/bin-map code. Use for any wafer, lot, "
                 "STDF, or yield-analysis question."
)

@mcp.tool()
def search_wafer_analysis(query: str, top_k: int = 5, file_ext: str = None) -> str:
    """Search wafer/STDF/yield analysis reference docs and past code.

    file_ext: optional filter, e.g. '.py' to restrict to code chunks only.
    """
    q_emb = embed_model.encode([query])[0].tolist()
    where = {"file_ext": file_ext} if file_ext else None
    results = collection.query(
        query_embeddings=[q_emb], n_results=top_k,
        include=["documents", "metadatas"], where=where
    )
    if not results["documents"] or not results["documents"][0]:
        return "No matching documents."
    parts = [
        f"[{meta.get('rel_path', 'unknown')}]\n{doc}"
        for doc, meta in zip(results["documents"][0], results["metadatas"][0])
    ]
    return "\n\n".join(parts)

if __name__ == "__main__":
    mcp.run()
```

This is your `retrieve_context()` function almost unchanged - same embed call, same `chroma_collection.query()`, same metadata formatting. The only real addition is the optional `file_ext` filter, which uses metadata you're already writing in `WEBRAG_INGEST.py` (`type`, `file_ext`) but weren't querying against yet.

Register it:

```bash
claude mcp add --transport stdio wafer-analysis-rag -- python3 mcp_servers/wafer_analysis_rag.py
```

Or as a persistent HTTP service on ai.local if you want it reachable from the MacBook too - see the prior discussion for the stdio-vs-http tradeoff.

**Lane 2 piece (unchanged): `WEBRAG_simple.py` as it stands today.** Full local generation, fully offline, for anything that shouldn't go near Anthropic's API. Don't touch this file. Run the two side by side - they read the same Chroma DB, they just serve different purposes.

---

### 4. Multi-collection design (broadening RAG type 1: domain-segmented vector search)

You already run separate collections per domain (`lab_automation`, `data_analysis`) with separate `WEBRAG_simple.py` deployments and tuned system prompts per domain. Formalize that as separate MCP servers rather than one generic "search everything" tool:

```
mcp_servers/
├── lab_automation_rag.py      # CHROMA_PATH=.../lab_automation, instruments/SCPI
├── wafer_analysis_rag.py      # CHROMA_PATH=.../data_analysis, STDF/yield
├── sipi_textbook_rag.py       # your two-stage OCR pipeline's output
└── code_patterns_rag.py       # past good code, cleared for general reuse
```

Same script shape as section 3a, just pointed at different `CHROMA_PATH`/`COLLECTION_NAME` and given a sharper `description` per domain. This matters more than it looks: Claude routes to a tool based on its description, the same way it routes to a skill. A single server with one ambiguous `search_everything` tool gives Claude no signal about which corpus is relevant; four servers with tight descriptions ("wafer yield and STDF" vs "instrument SCPI control") route correctly without you doing anything extra.

```bash
claude mcp add --transport stdio lab-automation-rag -- python3 mcp_servers/lab_automation_rag.py
claude mcp add --transport stdio wafer-analysis-rag -- python3 mcp_servers/wafer_analysis_rag.py
claude mcp add --transport stdio sipi-textbook-rag -- python3 mcp_servers/sipi_textbook_rag.py
```

Tool Search (on by default in Claude Code) keeps the cost of this low - tool schemas don't enter context until Claude actually searches for a relevant one, so adding more servers doesn't bloat every conversation.

---

### 5. Broadening RAG type 2: structured/exact query, not vector search

Not everything you'd call "RAG" should be vector search. Die-level STDF results, yield numbers, bin counts - these are tabular and you want exact answers, not the nearest semantically-similar chunk. Chunking a CSV into 256-word text blobs and embedding it loses the structure that makes it useful.

```python
# mcp_servers/wafer_data_sql.py
from mcp.server.fastmcp import FastMCP
import pandas as pd

DATA_PATH = "/home/alex/wafer_data/parsed_stdf.parquet"  # output of your
                                                            # STDF-to-CSV/PIR-PRR
                                                            # join pipeline

mcp = FastMCP(
    "wafer-data-sql",
    instructions="Exact lookups and aggregations over parsed STDF die-level "
                 "data: yield by lot/wafer, bin counts, parametric stats. "
                 "Use for numeric questions, not for explaining concepts."
)

@mcp.tool()
def query_wafer_yield(lot_id: str = None, wafer_id: str = None) -> str:
    """Yield, bin distribution, and pass/fail counts for a lot or wafer."""
    df = pd.read_parquet(DATA_PATH)
    if lot_id:
        df = df[df.LOT_ID == lot_id]
    if wafer_id:
        df = df[df.WAFER_ID == wafer_id]
    if df.empty:
        return "No matching records."
    yield_pct = (df.BIN == 1).mean() * 100
    bin_counts = df.BIN.value_counts().sort_index()
    return f"Yield: {yield_pct:.2f}%\n\nBin distribution:\n{bin_counts.to_string()}"

if __name__ == "__main__":
    mcp.run()
```

This is the same "expose a tool" pattern, just with `pandas` instead of `chromadb` underneath. The distinction worth keeping in mind going forward: vector RAG for "explain this" and "find similar code," structured query tools for "what's the actual number."

---

### 6. Broadening RAG type 3: multimodal RAG for schematics

You already built the pieces for this - the two-stage OCR pipeline for the SI/PI textbook (Tesseract classification + Claude vision API routing + PyMuPDF image extraction) and the manifest/index JSON from the Pi Zero 2W OCR work. This formalizes that into the same MCP pattern, with one addition: the tool returns a file path, and Claude reads the actual image afterward rather than relying on OCR text alone.

```python
# mcp_servers/schematics_rag.py
from mcp.server.fastmcp import FastMCP
import chromadb
from sentence_transformers import SentenceTransformer

CHROMA_PATH = "/home/alex/hugging_face_rag/chroma_db_schematics"
COLLECTION_NAME = "schematics"
EMBED_MODEL_NAME = "nomic-ai/nomic-embed-text-v1.5"

embed_model = SentenceTransformer(EMBED_MODEL_NAME)
chroma_client = chromadb.PersistentClient(path=CHROMA_PATH)
collection = chroma_client.get_or_create_collection(COLLECTION_NAME)

mcp = FastMCP(
    "schematics-rag",
    instructions="Search OCR'd schematic and datasheet pages by description. "
                 "Returns matched text plus the image file path - call Read "
                 "on that path afterward to actually view the schematic "
                 "before answering anything about pin layout, traces, or "
                 "component placement."
)

@mcp.tool()
def search_schematics(query: str, top_k: int = 3) -> str:
    """Find schematic/datasheet pages matching a description. Returns image
    paths - view them with Read before answering layout questions."""
    q_emb = embed_model.encode([query])[0].tolist()
    results = collection.query(
        query_embeddings=[q_emb], n_results=top_k,
        include=["documents", "metadatas"]
    )
    if not results["documents"] or not results["documents"][0]:
        return "No matching pages."
    parts = [
        f"image_path: {meta['image_path']}  (page {meta.get('page', '?')})\n"
        f"OCR text: {doc}"
        for doc, meta in zip(results["documents"][0], results["metadatas"][0])
    ]
    return "\n\n".join(parts)

if __name__ == "__main__":
    mcp.run()
```

Ingestion (extending `WEBRAG_INGEST.py`'s pattern to image-bearing pages):

```python
# add to your ingestion pass when processing a PDF/scan source
for page_num, image_path, ocr_text in extract_pages(pdf_path):  # your existing
                                                                    # PyMuPDF +
                                                                    # Tesseract step
    embedding = embed_model.encode([ocr_text])[0].tolist()
    chroma_collection.add(
        ids=[f"{pdf_path}_page_{page_num}"],
        embeddings=[embedding],
        metadatas=[{"image_path": str(image_path), "page": page_num, "source": pdf_path}],
        documents=[ocr_text]
    )
```

The retrieval step finds the right page by OCR'd text similarity; Claude's actual visual reasoning happens when it reads the returned image directly. Vector search is doing triage here, not the seeing.

---

### 7. Broadening RAG type 4: precision upgrades to your existing collections (lighter lift)

Two cheap additions that use metadata you're already writing in `WEBRAG_INGEST.py` and don't require new infrastructure:

**Metadata filtering** - you already tag `type` (code/text) and `file_ext` per chunk but the original `retrieve_context()` never queries against it. The `where` parameter added in section 3b's example is the whole change:

```python
results = collection.query(query_embeddings=[q_emb], n_results=top_k, where={"file_ext": ".tf"})
```

**Hybrid search (keyword + vector)** - pure embedding search misses exact-string matches like a specific register name or test number. Adding BM25 alongside vector search and merging results catches both:

```python
from rank_bm25 import BM25Okapi
# build once at server startup from the same documents you've already chunked
bm25 = BM25Okapi([doc.split() for doc in all_chunks])
keyword_hits = bm25.get_top_n(query.split(), all_chunks, n=top_k)
# merge keyword_hits with the vector results before returning
```

Neither of these is a new RAG type so much as making the existing collections more precise. Worth doing before adding more collections, since precision compounds - a better-targeted `lab_automation` search beats five mediocre new corpora.

---

### 8. Subagents - your personas, mapped directly

Your `WEBRAG_simple.py` `SYSTEM_PROMPT` for the wafer analyst is already excellent subagent material - the code-output policy, response format rules, and clarifying-question logic transfer almost verbatim. The only thing that changes is the `{{RAG_CONTEXT}}` static injection becomes a dynamic tool call.

```yaml
---
name: wafer-analyst
description: Wafer test data analysis - yield, parametric stats, STDF, bin maps, Cpk. Use for any wafer/lot/STDF/yield question or analysis script request.
tools: Read, Write, Edit, Bash, Grep, Glob, mcp__wafer-analysis-rag__search_wafer_analysis, mcp__wafer-data-sql__query_wafer_yield
model: sonnet
memory: project
---

## Code Output Policy
First response to any code request: minimal, flat, readable script only.
No classes. No error handling. No logging. No extras.
Only after the minimal version works, offer: "Want: [A] error handling
[B] multi-wafer loop [C] styled plot [D] Cpk table"
Never combine the minimal version and improvements in the same response.

## Core Responsibilities
1. Write minimal, clean Python for STDF, CSV, and JSON test data ingestion
2. Wafer-level metrics: yield, parametric distributions, bin maps, outliers
3. pandas for tabular data, numpy for statistics, matplotlib/plotly for plots
4. STDF: use pystdf or semi-ate/stdf libraries, never roll custom binary parsers
5. Mark unknown fields with # VERIFY: confirm with test engineer

## Script Header (include at top of every generated script)
# ASSUMED: 'BIN' column contains hard bin number
# ASSUMED: 'X_COORD', 'Y_COORD' are integer die coordinates
# VERIFY: confirm passing bin number with test engineer (often bin 1, not always)

Before answering, check search_wafer_analysis for relevant past patterns
and query_wafer_yield for any specific lot/wafer numbers needed.
```

```yaml
---
name: lab-automation-engineer
description: SCPI/VISA instrument control, PSU/scope/VNA scripting. Use for pyvisa, raw socket, or instrument programming requests.
tools: Read, Write, Edit, Bash, Grep, Glob, mcp__lab-automation-rag__search_lab_automation
model: sonnet
---

[your lab-automation SYSTEM_PROMPT, same transfer]
```

```yaml
---
name: qa-reviewer
description: Reviews code after engineer/analyst subagents finish. Use proactively after any implementation.
tools: Read, Grep, Glob, Bash
disallowedTools: Edit, Write
model: sonnet
memory: project
---

Review against the spec. Check: error handling, edge cases, the
ASSUMED/VERIFY headers are present and accurate, test coverage.
Report issues, do not fix them yourself.
```

`memory: project` gives the wafer-analyst and QA subagents their own persistent notes at `.claude/agent-memory/<name>/`, separate from the main session - they accumulate "patterns I keep flagging" across projects the same way your RAG corpus does, just at the persona level instead of the document level.

---

### 9. Hooks - enforcing what personas used to do by convention

Your JSON handoff protocol between personas relied on the model following it. A hook fires regardless of what the model decides:

```json
{
  "hooks": {
    "PostToolUse": [{
      "matcher": "Edit|Write",
      "hooks": [{"type": "command", "command": "./scripts/check-assumed-verify-headers.sh"}]
    }],
    "SubagentStop": [{
      "matcher": "wafer-analyst",
      "hooks": [{"type": "command", "command": "./scripts/log-to-memory.sh"}]
    }]
  }
}
```

`check-assumed-verify-headers.sh` can grep the just-written file for the `# ASSUMED:` / `# VERIFY:` header your system prompt requires and block the write (exit code 2) if it's missing - turning a prompt instruction into a guarantee.

---

### 10. CLAUDE.md and rules

```
project/
├── CLAUDE.md                     # build commands, file types, conventions
├── .claude/
│   └── rules/
│       ├── stdf-parsing.md       # paths: ["**/*.stdf", "**/pystdf/**"]
│       ├── v93k-syntax.md        # paths: ["**/*.tf", "**/*.spec", "**/*.lim"]
│       └── wafer-analysis.md     # paths: ["**/wafer_*.py", "**/yield_*.py"]
```

Path-scoped rules only enter context when Claude is actually touching matching files - the deterministic version of "retrieve only what's relevant" that vector search does probabilistically.

---

### 11. Query-time data flow

```
You: "what Cpk formula did we use for bin1 IDDQ on lot X23?"
   │
   ▼
Claude Code (wafer-analyst subagent active)
   │
   ├─► mcp__wafer-analysis-rag__search_wafer_analysis("Cpk bin1 IDDQ")
   │      embed query -> chroma.query() -> top-5 chunks -> text back
   │
   ├─► mcp__wafer-data-sql__query_wafer_yield(lot_id="X23")
   │      pandas filter/groupby -> exact numbers back
   │
   └─► Claude reasons over both, writes minimal script per your
          code-output policy, flags ASSUMED/VERIFY items
```

Two tool calls, two different retrieval mechanisms, one answer. This is the practical payoff of treating vector RAG and structured query as separate tools rather than forcing everything through one embedding search.

---

### 12. Final repo layout

```
your-project/
├── CLAUDE.md
├── .mcp.json                          # registers all MCP servers below
├── .claude/
│   ├── agents/
│   │   ├── wafer-analyst.md
│   │   ├── lab-automation-engineer.md
│   │   └── qa-reviewer.md
│   ├── skills/
│   │   ├── v93k-conventions/SKILL.md  # distilled, curated - not raw corpus
│   │   └── stdf-record-types/SKILL.md
│   ├── rules/
│   │   ├── stdf-parsing.md
│   │   └── v93k-syntax.md
│   └── settings.json                  # hooks, default permission mode
├── mcp_servers/
│   ├── lab_automation_rag.py          # = your retrieve_context(), no Llama
│   ├── wafer_analysis_rag.py
│   ├── sipi_textbook_rag.py
│   ├── schematics_rag.py
│   └── wafer_data_sql.py
└── WEBRAG_INGEST.py                   # unchanged, runs standalone per corpus
```

`WEBRAG_simple.py` (full version, with Llama) lives outside this repo entirely, on ai.local, as your Lane 2 system - it doesn't need to know Claude Code exists.

---

### Open decisions

> **OPEN:** one MCP server per domain (as built above) vs one server with a `collection` parameter on a single tool. Per-domain is more setup now but gives Claude sharper routing signal later as you add more corpora - recommend starting per-domain and only consolidating if server count gets unwieldy (10+).

> **OPEN:** where does `parsed_stdf.parquet` for the structured query tool get generated - a scheduled job off your existing STDF-to-CSV converter, or on-demand inside the MCP tool itself? On-demand is simpler but slower per query; scheduled is faster but adds a freshness question.

> **OPEN:** stdio vs persistent HTTP for the MCP servers - stdio is zero-setup if you're running Claude Code directly on ai.local via SSH, HTTP is better if you also want to drive these from the MacBook over Tailscale without re-spawning Python each session.

---

### 13. Verification against known implementation practices

The architecture above checked against patterns seen in production RAG systems and agentic coding setups elsewhere. Four tiers, ordered by how much they'd actually bite.

#### 13a. Tier 1 - bugs, fix before scaling

**Stale chunk cleanup on re-ingestion.** `WEBRAG_INGEST.py` IDs chunks as `{file_path}_chunk_{chunk_idx}`. Re-ingest an edited file that now produces fewer chunks than before, and the old trailing chunks never get deleted - they stay in Chroma forever, orphaned, still surfacing in search results for content that no longer exists in the file. Fix: delete all chunks matching `source == file_path` before re-adding, or query existing `total_chunks` for that source and explicitly drop anything beyond the new count.

**Error handling dropped in the MCP server rewrite.** The original `retrieve_context()` wraps the embed+query call in try/except and returns `"[RAG error]"` on failure. The section 3b MCP server example doesn't carry that over - if Chroma's locked or the embed model fails to load, it throws instead of degrading gracefully. Should be restored verbatim.

**Resource contention across MCP server processes.** Section 4's design runs five separate MCP servers (lab-automation, wafer-analysis, sipi-textbook, schematics, plus the SQL one), each independently loading `SentenceTransformer` into memory. On a shared 8GB 3070 also running Ollama and potentially `WEBRAG_simple.py`'s Qwen3.5-9B for Lane 2, that's wasteful at best and an OOM risk at worst. Fix: one shared embedding service all MCP servers call into, or CPU-pin the embedding step entirely - embedding a short query string is cheap enough to run on CPU, which removes GPU contention.

**No incremental re-indexing.** `WEBRAG_INGEST.py` does a full `os.walk` every run. Fine for occasional batch jobs, not viable for tracking an actively-changing codebase. Fix: track mtime or content hash per file, skip unchanged files, only re-embed what moved.

#### 13b. Tier 2 - retrieval quality, known weak points

Superseded and substantially extended by section 14 below once the document-conversion research came in - the original list is kept here for completeness.

- Word-count chunking is the wrong unit for code and V93K syntax: 256-word sliding windows routinely cut a function or a `.spec` testflow block in half.
- No reranking step: pulling top-20 by cosine similarity then reranking with a cross-encoder (`bge-reranker`, runs fine on CPU) down to the top 5 actually sent to Claude is a bigger precision lever than hybrid search alone.
- One embedding model across prose, code, and dense structured syntax: code-specific embeddings, or at minimum keeping code chunks in their own collection, consistently outperforms general embeddings on code retrieval.
- No eval loop: nothing checks whether retrieval is actually finding the right thing. Claude Code's own `skill-creator` plugin has this pattern built in (golden test queries, pass/fail grading, before/after benchmark) and the same discipline should apply to the MCP retrieval tools here.

#### 13c. Tier 3 - architecture choices not yet justified

**Subagent vs `--agent` for the wafer-analyst.** Subagents start with zero conversation history on every invocation - fine for isolated lookups, bad for the iterative back-and-forth ("now filter to lot X23," "now compare against last week's run") that data analysis usually is. Running the agent definition as the main thread instead (`claude --agent wafer-analyst`) keeps full conversational continuity while still swapping system prompt/tools/model. Subagent delegation fits the QA reviewer better, since that genuinely is a bounded "look at this, report back" task.

**Pure vector RAG for code is the weaker industry default now.** Tools like Sourcegraph Cody and GitHub Copilot lean on symbol/AST-aware search (LSP, call graphs, references) combined with embeddings, not embeddings alone. Section 8's `code-intelligence` plugins (`pyright-lsp`, `clangd-lsp`) cover this directly. For the past-code corpus specifically: lean on Grep/Glob over an actual checked-out reference repo plus code-intelligence plugins, and reserve vector RAG for the genuinely fuzzy stuff (docs, schematics, prose).

**Hook and QA subagent overlap, unclear division.** Section 9's `PostToolUse` hook (grep for the `ASSUMED/VERIFY` header) and the QA subagent (general code review) currently both do vague "review the output" duty. Clean split: hooks for deterministic, syntactic checks (header present or not), subagent for semantic correctness (is the assumption actually reasonable, does the Cpk formula match the spec).

**No ground-truth verification loop.** The strong version of "give Claude a way to verify its work" for STDF parsing specifically is a small fixture - a sample STDF file with known yield/bin numbers - that generated parsing code runs against before it's trusted, not just a style review. Given verification is part of the actual consulting pitch (test pattern verification), this is a real gap rather than a nice-to-have.

#### 13d. Tier 4 - worth knowing about, lower priority at this scale

**HyDE / LLM-enriched chunks at ingestion.** Generating a short synthetic summary per chunk with a cheap local model before embedding, instead of embedding raw text, is a known technique that improves retrieval over vanilla chunk-and-embed. Adds an ingestion-time LLM pass - more complexity than likely needed yet.

**Graph-based retrieval (GraphRAG) for multi-hop questions** ("what tests touch components from this schematic") exists in production systems handling highly interconnected technical knowledge. Likely overkill until the schematics/test-program corpus is large enough that multi-hop questions come up often.

**No observability on retrieval itself.** Logging what was queried and what came back, even to a flat file, would surface retrieval failures directly instead of inferring them from bad downstream answers.

---

### 14. RAG-ready document conversion, verified against research

The single biggest gap in section 13's retrieval-quality critique: it jumped straight to retrieval-layer fixes (reranking, hybrid search, code-aware chunking) without addressing extraction quality at all. For mechanics/hardware docs, schematics, and the SI/PI textbook specifically, extraction is upstream of everything else and likely the dominant loss source - no reranker recovers a formula that was already OCR'd into garbage before it reached the vector DB.

> **DECISION:** prioritize extraction quality above reranking. Clean extraction with mediocre retrieval still returns usable content; garbage extraction with perfect retrieval still returns garbage.

#### Why classic OCR fails on technical content

Classic OCR engines are trained on prose. They have no model of two-dimensional mathematical layout - subscripts, nested fractions, matrices, and register tables defeat a line-by-line text recognizer because it reads visual shapes as if they were ordinary words read left to right. This isn't a tuning problem solvable with a higher DPI scan, it's an architectural mismatch. A real example from OCR run on a signal-integrity textbook page:

```
Lyie-via = 21 xhx n(B) pit (13-35)
```

What it was supposed to be:

$$L_{via\text{-}via} = 2 \times h \times \ln\left(\frac{B}{D}\right) \quad \text{[pH]} \tag{13-35}$$

The OCR output isn't just imprecise, it's actively wrong in a way that misleads both a human skimming it and an embedding model representing it semantically - worse than no extraction at all, because it carries false confidence.

**Table 3 - conversion method comparison for technical PDF content**

| Method | Formulas | Tables | Cost | Best for |
|---|---|---|---|---|
| Tesseract / classic OCR | Poor | Poor | Free, fast | Plain prose pages only |
| `pdfplumber` / `camelot` | N/A | Good | Free, fast | Born-digital PDFs with text layer + visible table structure |
| Mathpix (math OCR) | Very good | Good | ~$0.002-0.005/page | High-volume formula-heavy documents |
| Vision-capable LLM | Very good | Very good | ~2,000-2,300 tok/page | Mixed content - formulas + tables + figures + prose together, scanned PDFs with no text layer |

#### Target format: structured Markdown, four rules

1. **Headers define chunk boundaries.** `##`/`###` per section, each section written to be understandable in isolation - a chunk should make sense retrieved alone, without relying on "as mentioned above."
2. **Formulas as LaTeX, with symbol definitions attached.** The definition list isn't optional decoration - without it, a retriever can match the equation but the LLM has no way to explain what the variables mean.
3. **Tables as real Markdown tables, never flattened to prose.** Column structure preserved means a retriever returns one complete, correct row (symbol, value, unit, condition all attached) instead of numbers floating free of their meaning.
4. **Images inline at point of reference, with a manifest.** An HTML comment (`<!-- figure-ref: Figure 13-38 -->`) carries machine-readable metadata invisibly to a RAG indexer while staying invisible to a human reading it rendered.

#### Hybrid routing pipeline (already partially built)

```
1. Diagnostic pass        pdfinfo / pdffonts / sample pdftotext
2. Page classification    cheap, local heuristics, no API calls
                           -> route: "prose" | "vision" | "figure_only"
3. Routed extraction      prose -> Tesseract (cleaned)
                           vision -> LLM, RAG-ready contract enforced
4. Assembly                ebook.md + images/ + manifest.json
```

This is the same shape as the existing two-stage SI/PI textbook pipeline (Tesseract classification + Claude vision API routing + PyMuPDF image extraction). Cost concretely: ~46K tokens for a 21-page excerpt, ~220K for 100 pages, ~1.7-2M for an 800-page document routed entirely through vision, ~500-700K for the same 800 pages hybrid-routed - the hybrid split is usually where the real savings live, since formulas and tables cluster in specific sections rather than spreading evenly.

#### Chunking, refined

- **Structural boundaries beat fixed-token splitting** for documents where a formula derivation or a register's bit-field table needs to stay intact as a unit. A fixed split has no awareness of where a table starts and ends and can sever it mid-structure.
- **Chunk size depends on query type**: 256-512 tokens for factoid lookups, 512-1024 for multi-step technical explanations requiring multi-concept reasoning. The current `CHUNK_SIZE = 256` in `WEBRAG_INGEST.py` sits at the factoid end - reasonable for V93K dense config lookups, likely too small for SI/PI textbook content needing a full derivation.
- **Overlap is less settled than it used to be.** A January 2026 systematic analysis (SPLADE retrieval, Mistral-8B, Natural Questions) found overlap provided no measurable benefit and only increased indexing cost - directly relevant since `WEBRAG_INGEST.py`'s `CHUNK_OVERLAP = 50` (20%) was set on the older default assumption. Worth testing against the actual corpus rather than assuming the figure is still right.
- **Hierarchical (parent/child) chunking** - small chunks for retrieval matching, a larger parent chunk returned to the LLM for context - is the most widely adopted production pattern for mixed-density documents in 2025-2026. For a single-engineer offline pipeline, structural chunking alone likely gets most of the benefit without the added complexity of maintaining two index layers; worth treating as the next lever only if structural chunking alone proves insufficient.

**Table 4 - practical chunking defaults**

| Parameter | Starting point |
|---|---|
| Chunk boundary | Structural (page/section headers) |
| Chunk size | 256-512 tok factoid, 512-1024 tok analytical |
| Overlap | Start at 0-10%, increase only if observed loss |
| Tables/registers | Keep whole, never split mid-table |
| Formulas | Keep formula + definitions as one atomic unit |

#### JSON vs Markdown: refining section 5's structured-query tool

Section 5 proposed `wafer_data_sql.py` for exact yield/bin lookups specifically. The general principle is broader: any enumerable, exact-match data wants exact-match retrieval, not vector similarity - the same reasoning extends to V93K `.lvl`/`.tim`/`.pin` parameter files, which `WEBRAG_INGEST.py` currently chunks by word count and embeds like prose, the exact mistake this principle warns against.

The clearest precedent is register bit-fields - ARM's CMSIS-SVD format already solves this for embedded systems, describing every register and bit-field as structured data (name, address offset, reset value, access type, enumerated meanings) rather than narrative. A query like "what does CMS=01 mean on TIM2_CR1" resolves as one exact field lookup against JSON; the same data flattened into a Markdown table and embedded has no concept of "look up row where field=X and value=Y," only "text semantically close to the query wording," which risks surfacing the wrong row entirely.

> **DECISION:** for register/bit-field and V93K parameter content, generate JSON as the primary artifact during conversion, with a Markdown table alongside purely for human skimming - not the reverse.

Two more places JSON earns its place, both directly relevant here:

- **Image/figure manifest** - figure number -> file path -> source page -> caption -> section. This is a more concrete schema than section 6's `schematics_rag.py` sketch (which only returned `image_path` and `page` from chunk metadata) and should replace it:

```json
{
  "figures": {
    "fig_p012_a.png": {
      "page": 12,
      "figure_number": "13-38",
      "caption": "Where should the capacitor go - on the same surface as the BGA or directly under the BGA?",
      "section": "Capacitor Placement Relative to the BGA",
      "path": "images/fig_p012_a.png"
    }
  }
}
```

- **Table of contents / document index** - section -> page range -> file, answers "which chapter" without running semantic search at all.

This validates the multi-MCP-server design from section 4 independently: current survey work on knowledge-oriented RAG describes production systems running multiple parallel indexes rather than one - vector embeddings for semantic search, structured indexes for exact relationships, hierarchical indexes for category navigation - pulling from whichever index fits the query type. The Markdown/JSON split is the document-level version of the same principle already built into this blueprint's server-per-domain architecture.

#### The gap between this research and the running pipeline

`WEBRAG_INGEST.py` as it stands implements none of this yet - plain UTF-8 read, word-count chunking uniformly across every file type, no vision-LLM routing, no LaTeX preservation, no JSON sidecar generation. The two-stage OCR work already done for the SI/PI textbook (Tesseract classification + Claude vision routing) is the right shape for the hybrid pipeline described above, but the uploaded ingestion script is currently a separate, simpler tool that doesn't call into it. Closing this gap is the highest-leverage item in this entire document once extraction priority is accepted.

---

### 15. Recommended skills and plugins for this line of work

#### Official marketplace plugins (`/plugin install <name>@claude-plugins-official`)

| Plugin | One-line |
|---|---|
| `pyright-lsp` | Python type-checking and go-to-definition for the FastAPI/ChromaDB/MCP server code, requires `pyright-langserver` installed |
| `clangd-lsp` | C/C++ code intelligence for the BeagleBone PRU and SPI DAQ work, requires `clangd` installed |
| `github` | Pre-configured MCP connection to GitHub so Claude can read issues/PRs on the `student45667` repos without manual setup |
| `commit-commands` | Adds `/commit`-style skills for staging, writing commit messages, and opening PRs |
| `security-guidance` | Reviews every edit for common vulnerabilities and fixes them in the same session, relevant once client data touches these pipelines |
| `pr-review-toolkit` | Specialized review agents, worth it once freelance work means other people's PRs land in the queue |
| `mcp-server-dev` | Scaffolds new MCP servers from a description, useful given how many are being built here (lab-automation, wafer-analysis, schematics, etc.) |

#### Custom skills worth building for this domain

Not installable - the shape of skill people doing RAG-over-technical-docs and hardware test engineering typically write for themselves once a pattern repeats a few times.

| Skill | One-line |
|---|---|
| `pdf-to-rag-conversion` | Codifies section 14's checklist (LaTeX formulas, real Markdown tables, image manifest, structural chunking) so Claude follows it automatically on every new datasheet conversion |
| `mcp-rag-server-pattern` | The FastMCP + Chroma + embedding boilerplate from section 3b as a template, so the 5th domain-specific MCP server is "fill in the collection name" instead of written from scratch |
| `stdf-record-types` | Reference for PIR/PRR/PTR/FTR field names and the die-index join pattern, so Claude stops re-deriving STDF structure from scratch each session |
| `v93k-syntax-conventions` | Already planned in section 12 - testflow/testsuite/pattern block structure for `.tf`/`.spec`/`.lim` files |
| `chunking-defaults` | Table 4 above as a standing reference, so every new ingestion script starts from tested defaults instead of word-count-256 by habit |
| `register-bitfield-json` | The CMSIS-SVD-style JSON schema from section 14 as a template for any new register/parameter table converted, keeping the shape consistent across datasheets |

`pdf-to-rag-conversion` and `mcp-rag-server-pattern` carry the highest payoff of the six, given how much of section 14's conversion work and section 4's server-per-domain pattern are about to repeat.

