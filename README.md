# Guides, Studies & Articles — AI Topics

A growing collection of study notes, technical guides, and articles on
AI/ML topics — written while building local and offline AI tooling for
semiconductor and embedded engineering workflows (RAG pipelines, document
conversion, agentic systems). Each piece pairs a Markdown version, suitable
for RAG ingestion, version control, and quick reading, with an interactive
HTML version for a richer reading experience.

## Contents

| Topic | Markdown | Interactive HTML |
|---|---|---|
| What are ideal materials for RAG with minimal loss? — a guide to converting technical PDFs (formulas, tables, images) into RAG-ready documents without information loss | [rag_minimal_loss_guide.md](./rag_minimal_loss_guide.md) | [Open rendered preview ↗](https://htmlpreview.github.io/?https://github.com/student45667/guides_studies_articles/blob/main/rag_minimal_loss_guide.html) |
| Claude Code + RAG System — a blueprint for combining a local offline RAG / three-persona pipeline (ChromaDB, llama.cpp) with Claude Code's native primitives (CLAUDE.md, subagents, skills, MCP servers, hooks), verified against known production RAG practices | [claude-rag-blueprint-combined.md](./claude-rag-blueprint-combined.md) | [Open rendered preview ↗](https://htmlpreview.github.io/?https://github.com/student45667/guides_studies_articles/blob/main/claude-rag-blueprint.html) |

> The interactive HTML link uses [htmlpreview.github.io](https://htmlpreview.github.io/)
> to render the `.html` file live in-browser straight from GitHub —
> GitHub itself only shows HTML files as source code, not rendered
> output, so this prefix trick is what makes the interactive version
> clickable directly from this README, same pattern as
> [3Persona_model/ai_three_personas.html](https://htmlpreview.github.io/?https://github.com/student45667/3Persona_model/blob/main/ai_three_personas.html).

## How to read

- **Markdown files** render directly on GitHub/GitLab, or open in any
  editor — these are also the canonical RAG-ready source, formatted per
  the conventions described in the RAG guide itself (LaTeX formulas,
  real Markdown tables, captioned inline images, self-contained sections).
- **HTML files** are standalone interactive documents. Three ways to view them:
  1. **Rendered preview link above** (htmlpreview.github.io) — one click, no download, works straight from the README.
  2. **Clone and open locally** — `open rag_minimal_loss_guide.html` (macOS) or double-click the file after cloning.
  3. **GitHub Pages**, if enabled on this repo — see note below.

  All three require an internet connection on first load, since the
  page fetches fonts and the KaTeX renderer from a CDN.

## Topics covered so far

- Converting technical PDFs (datasheets, scope manuals, engineering
  textbooks) to RAG-ready Markdown with minimal information loss
- Why classic OCR fails on formulas and tables, and when to route to
  vision-based transcription instead
- Hybrid extraction pipelines for large documents (cost-aware routing)
- Chunking strategy and structure for technical-document RAG
- Mapping an existing local/offline RAG and three-persona AI pipeline
  onto Claude Code's native primitives (CLAUDE.md, subagents, skills,
  MCP servers, hooks, worktrees)
- Domain-segmented MCP server architecture: vector search vs.
  structured/exact-match retrieval for engineering data (STDF records,
  register bit-fields)
- Verifying a RAG architecture against known production implementation
  practices and document-conversion research

More studies will be added here as they're written.

## Optional: GitHub Pages instead of htmlpreview

For a more permanent setup once there are several HTML guides, enabling
GitHub Pages on this repo (Settings → Pages → Deploy from branch →
`main` → `/ (root)`) serves every `.html` file directly at:

```
https://student45667.github.io/guides_studies_articles/rag_minimal_loss_guide.html
```

No proxy dependency, faster load, and works the same way local opening
does. The htmlpreview.github.io links above remain useful as a
zero-setup fallback or for one-off shares.

---

