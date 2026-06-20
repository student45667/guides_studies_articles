# What Are Ideal Materials for RAG With Minimal Loss?

<!-- manifest:
  topic: RAG-ready document formatting and conversion
  generated: 2026-06-20
  format_version: 1.0
  audience: engineers building local/offline RAG pipelines from technical PDFs
-->

> A practical guide to producing documents — datasheets, scope manuals,
> textbooks, technical references — that are simultaneously human-readable
> and loss-free when ingested into a Retrieval-Augmented Generation (RAG)
> pipeline. Written from the perspective of someone converting real
> engineering PDFs (formulas, register tables, schematics) where standard
> OCR actively destroys the information a RAG system needs.

---

## Page 1 — The Problem: PDFs Were Never Meant to Be Read by Machines {#page-1}

A PDF is a print format. It encodes where ink goes on a page — glyph
shapes at X/Y coordinates, image blobs, vector line drawings — not the
semantic structure of the content. A human reading a rendered PDF
reconstructs that structure effortlessly: this is a table, this is a
formula, this sentence continues from the previous line. A naive
text-extraction pipeline does none of that reconstruction. It just reads
glyphs in roughly the order they appear and concatenates them.

This mismatch is invisible for plain prose and catastrophic for anything
structured. Three content types account for nearly all of the
information loss in technical documents:

**Tables** lose column alignment entirely. A register map or an
electrical-characteristics table becomes a flat stream of numbers with no
indication of which value belongs to which symbol, row, or column.

**Formulas** get read as if they were regular words. Subscripts,
superscripts, Greek letters, fraction bars, and operators like
$\ln$, $\sum$, $\sqrt{}$ all collapse into garbled character soup. A real
example, from OCR run on a signal-integrity textbook page:

```
Lyie-via = 21 xhx n(B) pit (13-35)
```

What this was actually supposed to be:

$$L_{via\text{-}via} = 2 \times h \times \ln\left(\frac{B}{D}\right) \quad \text{[pH]} \tag{13-35}$$

The OCR output isn't just imprecise — it's actively wrong in a way that
would mislead both a human skimming the converted text and an embedding
model trying to represent it semantically. This is worse than no
extraction at all, because it carries false confidence.

**Images** get extracted as disconnected binary blobs, severed from the
caption and paragraph that reference them ("Figure 13-32 illustrates...").
A page-by-page dump produces a pile of `img_001.png`, `img_002.png` files
with no link back to where they belong in the narrative.

> **DECISION:** the fix is not a better OCR engine — it's choosing the
> right *target format* first, then choosing a conversion method capable
> of hitting that target. Format and method are separate decisions, and
> getting the format right first clarifies what the method needs to
> achieve.

---

## Page 2 — The Target Format: Structure-Preserving Markdown {#page-2}

The format that satisfies both "human-readable" and "RAG-ready"
simultaneously is structured Markdown with a few conventions layered on
top. Plain Markdown alone isn't enough — the conventions matter as much
as the base format.

### Why Markdown over alternatives

| Format | Human-readable | Machine-parseable | Renders formulas/tables | Notes |
|---|---|---|---|---|
| Plain `.txt` | Yes | Poor | No | No structure signal at all |
| Raw OCR output | Barely | Poor | No | The failure mode described above |
| `.docx` | Yes | Moderate | Limited | Binary format, harder to diff/version, fine for delivery but not as an intermediate working format |
| `.html` | Yes (rendered) | Good | Yes (with MathML/KaTeX) | Heavier, more markup noise per byte of content |
| **Markdown + LaTeX + JSON sidecars** | **Yes** | **Yes** | **Yes** | Lightweight, diffable, git-friendly, directly chunkable |

Markdown wins for this use case because it's the lowest-overhead format
that still carries structure: headers signal section boundaries,
table syntax preserves column alignment as text, and LaTeX delimiters
(`$...$`, `$$...$$`) are a widely-supported convention for embedding math
as parseable text rather than as an unparseable image.

### The four structural rules that matter most

**1. Headers define chunk boundaries.** Use `##` for major sections and
`###` for subsections, with each section written to be understandable in
isolation — a chunk should make sense if retrieved alone, without the
rest of the document for context. This directly addresses what Anthropic's
research on contextual retrieval identified as the core failure mode of
naive chunking: a fragment like *"the company's revenue grew by 3% over
the previous quarter"* is useless on retrieval because it doesn't say
which company or which time period it refers to. The practical
implication for document *authoring* (not just chunking after the fact)
is to write each section so it restates its subject rather than relying
on "as mentioned above."

**2. Formulas as LaTeX, always, with symbol definitions attached.**

```markdown
$$L_{via\text{-}via} = 2 \times h \times \ln\left(\frac{B}{D}\right) \quad \text{[pH]} \tag{13-35}$$

where:
- $L_{via\text{-}via}$ — loop spreading inductance between vias, pH
- $h$ — dielectric thickness between vias, mils
- $B$ — distance between via centers, mils
- $D$ — via diameter, mils
```

The definition list is not optional decoration. Without it, a retriever
can match the equation to a query but the LLM generating an answer has no
way to explain what the variables mean — the definitions are what make
the chunk self-contained.

**3. Tables as real Markdown tables, never flattened to prose.**

```markdown
| Symbol | Parameter | Min | Typ | Max | Unit | Conditions |
|---|---|---|---|---|---|---|
| $f_{SCK}$ | SCK clock frequency, master mode | — | — | 18 | MHz | $C_L$ = 30 pF |
| $t_{su(MI)}$ | MISO data setup time before SCK edge | 5 | — | — | ns | — |
```

Column structure preserved means a retriever can return one complete,
correct row — symbol, value, unit, and condition all attached to each
other — instead of numbers floating free of their meaning.

**4. Images placed inline at their point of reference, with stable
filenames and a manifest.**

```markdown
![Figure 13-38: Where should the capacitor go?](./images/fig_p660_a.png)
*Figure 13-38 — Cross-section showing capacitor placement options.*

<!-- figure-ref: Figure 13-38 -->
```

The HTML comment carries machine-readable metadata invisibly — visible to
a RAG indexer parsing the raw file, invisible to a human reading it
rendered.

---

## Page 3 — Conversion Method: Why Vision-Based Transcription Beats OCR for Technical Content {#page-3}

Choosing the target format is the easy part. Actually producing it from a
scanned or graphic-format PDF is where the real engineering decision
sits, and it depends entirely on what the source content looks like.

### The OCR ceiling

Classic OCR engines (Tesseract, and similar rule-based or CRNN-style
text recognizers) are trained on prose. They have no model of
two-dimensional mathematical layout — subscripts, nested fractions,
matrices, and nonstandard symbol sequences defeat a line-by-line text
recognizer because it reads the visual shapes as if they were ordinary
words read left to right.

This isn't a tuning problem solvable with a higher DPI scan. It's an
architectural mismatch between what the tool was built to recognize and
what's on the page.

### What actually works now

A late-2025 benchmark comparing document parsers specifically on
mathematical formula extraction found a wide spread in accuracy, with
the top performers being vision-language models and specialized
document-OCR systems rather than traditional rule-based parsers — state-of-the-art vision-language models and specialized document OCR systems achieve scores exceeding 9.6 out of 10, while traditional rule-based parsers and general-purpose models without document specialization perform considerably weaker. The practical takeaway: formula-heavy pages need either a specialized math-OCR tool or a general vision-capable LLM — not a traditional OCR pipeline.

**Table 1 — Conversion method comparison for technical PDF content**

| Method | Formulas | Tables | Cost | Best for |
|---|---|---|---|---|
| Tesseract / classic OCR | Poor (garbled) | Poor (no column structure) | Free, fast | Plain prose pages only |
| `pdfplumber` / `camelot` table extraction | N/A | Good | Free, fast | Born-digital PDFs with text layer + visible table structure |
| Mathpix (specialized math OCR) | Very good | Good | ~$0.005/page (API) | High-volume formula-heavy documents, dedicated budget |
| Vision-capable LLM (Claude, GPT-4V, Gemini) | Very good | Very good | Higher per-page token cost | Mixed content (formulas + tables + figures + prose context together), scanned/graphic PDFs with no text layer |

A specialized tool like Mathpix is now independently benchmarked at the
top tier for formula recognition specifically, with public reporting
describing it as the most accurate OCR technology with deep STEM functionality, including math, chemistry, handwriting, tables, foreign languages, and full PDF document conversion. For documents that are formula-dense throughout — a pure math textbook, for instance — a dedicated math-OCR API can be more cost-effective per page than a general vision LLM.

For mixed engineering documents — datasheets and SI/PI textbooks with
prose, formulas, tables, register maps, and figures all interleaved on
the same pages, often referencing each other ("see Table 24" appearing
mid-paragraph next to a formula) — a general vision-capable LLM has an
advantage that pure math-OCR tools don't: it can read the *whole page in
context* and decide how to format each piece relative to the surrounding
narrative, rather than extracting formulas and tables as isolated
fragments that still need to be manually stitched back into the prose
afterward.

> **OPEN:** for any specific large conversion job, the right choice
> between "specialized tool + manual reassembly" and "general vision LLM
> doing everything in one pass" comes down to formula/table density and
> budget — worth piloting both on a 10–20 page sample before committing
> to one path for an 800-page document.

---

## Page 4 — Practical Pipeline: Hybrid Routing to Control Cost {#page-4}

Running every page of a large document through a vision-capable LLM is
accurate but not always necessary, and for documents in the hundreds of
pages, cost and time add up. Most technical books and datasheets are not
uniformly dense — formulas and tables cluster in specific sections, while
long stretches remain plain prose that classic OCR handles perfectly well.

### The hybrid routing pattern

```
1. Diagnostic pass
   pdfinfo doc.pdf          # page count, size
   pdffonts doc.pdf         # text layer present? -> born-digital vs scanned
   pdftotext -f 1 -l 1 doc.pdf -   # sample the text layer if present

2. Page classification pass (cheap, local, no API calls)
   - Run fast/low-DPI Tesseract on every page
   - Score each page's OCR output for:
     * formula density (math symbols, equation-number patterns like "(13-35)")
     * table density (short, numeric-heavy lines with irregular spacing)
     * register/bit-field vocabulary ("bit", "0x4", "RESERVED", ALL_CAPS names)
   - Also check structural image coverage per page via PyMuPDF
     (how much of the page area is covered by embedded images)
   - Route each page: "prose" | "vision" | "figure_only"

3. Routed extraction
   - "prose" pages       -> Tesseract output, cleaned (rejoin hyphenated
                             line-wraps, collapse mid-paragraph newlines)
   - "vision"/"figure_only" pages
                          -> sent to a vision-capable LLM with a prompt
                             enforcing the structural rules from Page 2
                             of this guide (LaTeX formulas, Markdown
                             tables, inline image placement)

4. Assembly
   - Combine all pages into one ebook.md in page order
   - Extract embedded images via PyMuPDF, page-numbered filenames
   - Generate a manifest.json indexing page -> figures/tables/sections
```

> **DECISION:** classify before transcribing, not during. Running the
> cheap classification pass first lets you see the full cost estimate
> (page count routed to the expensive path × tokens/page) *before*
> spending anything, and lets you spot-check or manually override
> borderline pages.

### Cost estimation, concretely

For a vision-LLM pass at roughly 150 DPI: a rasterized page image costs
approximately 1,600 input tokens, and a typical structured-Markdown
transcription output runs 400–700 tokens, for a per-page total around
2,000–2,300 tokens.

**Table 2 — Estimated cost by document size (vision-route pages only)**

| Pages routed to vision | Estimated tokens | Notes |
|---|---|---|
| 21 (small excerpt) | ~46,000 | Comfortably fits in a single chat conversation |
| 100 | ~220,000 | Still chat-feasible in batches, or a short script |
| 800 (full textbook, if ALL pages routed to vision) | ~1.7–2,000,000 | Needs an API batch script, not chat |
| 800 (hybrid: ~30% formula/table-dense, 70% prose) | ~500,000–700,000 | Realistic estimate for most engineering textbooks once routing splits the load |

The hybrid split is usually where the real savings live — a textbook
with formulas concentrated in specific chapters rather than spread
evenly across all 800 pages can cut total vision-route cost by more than
half compared to routing every page through the expensive path
indiscriminately.

---

## Page 5 — Choosing Chunk Size and Structure for Retrieval {#page-5}

Getting the source document into clean structured Markdown solves the
*extraction* half of the problem. The other half — how that document gets
split into retrievable chunks once it's indexed — has its own set of
practical defaults worth knowing.

### Chunk size

Current practitioner guidance converges on a starting range rather than
one fixed number, with the right choice depending on query type: 512-1024 tokens for analytical queries requiring multi-concept reasoning, 128-256 tokens for factoid lookups like dates or names, with recursive chunking at 512 tokens with 15-20% overlap as a reasonable baseline before testing more elaborate strategies.

For technical engineering documents specifically — where a single
formula derivation, a complete register's bit-field table, or one
electrical-characteristics table often needs to stay intact as a unit —
chunking on the structural boundaries already present in the document
(the `## Page N` or `### Section` headers from the format in Page 2 of
this guide) tends to outperform fixed-token-count splitting, since a
fixed split has no awareness of where a table or formula starts and ends
and can sever them mid-structure.

### Overlap: less settled than it used to be

The traditional guidance has been modest overlap between adjacent
chunks — 10-20% as a starting point, for a 500-token chunk, 50-100 tokens of overlap — to avoid losing context at chunk boundaries. More recent evaluation work complicates this: a systematic analysis using SPLADE retrieval and Mistral-8B on Natural Questions found that overlap provided no measurable benefit and only increased indexing cost. The practical takeaway is to treat overlap as something to test against your own corpus and query patterns rather than assume as a default — for documents already chunked along natural structural boundaries (sections, pages, tables), the case for overlap is weaker than for arbitrary fixed-size splitting in the first place.

### Hierarchical chunking for mixed-density documents

For a document like an engineering textbook — long prose sections
interspersed with dense formula/table pages — a two-layer approach is
worth considering: small, precise child chunks for retrieval matching
(e.g., one formula + its definitions, or one table), paired with a larger
parent chunk (the full page or section) returned to the generating LLM
for context. This pattern is described as the most widely adopted production pattern in 2025–2026 because it resolves the fundamental precision-context trade-off: small chunks for finding, larger chunks for understanding, at the cost of maintaining two index layers and more complexity when source documents change, since both levels must be refreshed.

For a single-engineer offline pipeline (rather than a large production
system), this complexity may not be worth it — the structural chunking
described in Page 2 of this guide (page/section-bounded chunks, each
self-contained) gets most of the benefit without a second index layer,
and is the right starting point before reaching for hierarchical
chunking specifically.

### Practical defaults to start with

| Parameter | Starting recommendation | Adjust if... |
|---|---|---|
| Chunk boundary | Structural (page/section headers) | Document has very long, undifferentiated prose sections — fall back to recursive token-based splitting within those |
| Chunk size | 256–512 tokens for factoid lookups, 512–1024 for multi-step technical explanations | Queries consistently need more/less surrounding context than retrieved |
| Overlap | Start at 0–10% | Increase only if you observe boundary-context loss in actual retrieval failures, not preemptively |
| Tables/registers | Keep whole, never split mid-table | Table is unusually large (multi-page) — split by logical row groups, not arbitrary token count |
| Formulas | Keep formula + symbol definitions as one atomic unit | Never split a formula from its definition list |

---

## Summary: The Minimal-Loss Checklist

For any technical PDF headed into a RAG pipeline, minimal information
loss comes down to five checks, roughly in order of impact:

1. **Are formulas LaTeX, not OCR'd math?** If you see garbled symbol
   soup instead of `$...$` notation, the conversion method is wrong —
   route those pages to a vision-capable LLM or a specialized math-OCR
   tool, not classic OCR.

2. **Are tables still tables?** Markdown table syntax with aligned
   columns, not numbers flattened into prose or scrambled line order.

3. **Are images linked to their reference point, with a manifest?**
   Captioned, inline-placed, and indexed in a JSON sidecar mapping
   figure number → file path → source page, so a RAG answer can resolve
   "see Figure 13-38" to an actual file your application can serve.

4. **Is prose reconstructed into real sentences?** Not OCR
   line-fragments broken at the page's physical line wraps — a sentence
   spanning two printed lines should be one sentence in the converted
   text, hyphenation rejoined.

5. **Does each chunk make sense read in isolation?** Section headers
   present, no reliance on "as mentioned above," symbol definitions
   attached to their formulas, table context (units, conditions) kept
   with the table.

The underlying principle across all five: **minimal RAG loss comes from
preserving semantic structure, not from any particular file format.**
Markdown with LaTeX and JSON sidecars is simply the most convenient
container for carrying that structure — what matters is that tables stay
tabular, formulas stay mathematical, images stay linked to their context,
and paragraphs stay readable as paragraphs, all the way from the original
PDF page through to the chunk a retriever hands back to the LLM.

---

## Appendix — Worked Examples: Bad vs. Good for Each Checklist Item {#page-6}

Each example below shows realistic "what you'll actually see from OCR"
on the left and the target structure on the right, as it should appear
in the final `.md` file.

### 1. Formulas — LaTeX, not OCR'd math

**Bad — raw OCR output (do not ingest this into RAG):**

```markdown
Lyie-via = 21 xhx n(B) pit (13-35)

For example, if the via diameters are 10 mils and they are spaced
1 inch apart, in a pair of planes with h = 10 mils, the spreading
inductance is approximately:

Lyie-via = 2 10 In(1000/10) = 967 pH = 1nH (13-36)
```

The symbols, the multiplication operator, the natural-log function, and
the subscript have all been flattened into nonsense. This is unusable
both for a human reading it and for an embedding model — it doesn't even
fail safely, it asserts something false-looking with full confidence.

**Good — vision-transcribed, LaTeX:**

```markdown
The spreading loop inductance between the two via contacts is given by:

$$L_{via\text{-}via} = 2 \times h \times \ln\!\left(\frac{B}{D}\right) \quad \text{[pH]} \tag{13-35}$$

where:
- $L_{via\text{-}via}$ — the loop spreading inductance in the planes
  between the two via contacts, in pH
- $h$ — the dielectric thickness between the vias, in mils
- $B$ — the distance between the via centers, in mils
- $D$ — the diameter of the vias, in mils

For example, if the via diameters are 10 mils and they are spaced
1 inch apart, in a pair of planes with $h = 10$ mils, the spreading
inductance is approximately:

$$L_{via\text{-}via} = 2 \times 10 \times \ln\!\left(\frac{1000}{10}\right) \approx 967\ \text{pH} \approx 1\ \text{nH} \tag{13-36}$$
```

Renders correctly, embeds meaningfully (an embedding model can represent
"ln", "via-via", "pH" as real tokens), and a human can verify it against
the original page at a glance.

---

### 2. Tables — real Markdown tables, not flattened prose

**Bad — OCR output with column alignment lost:**

```markdown
fSCK SCK clock frequency master mode 18 MHz CL 30 pF
tr tf SCK rise fall time 8 ns CL 30 pF
tsu MI MISO data setup time before SCK edge 5 ns
th MI MISO data hold time after SCK edge 4 ns
tv MO MOSI data valid time after SCK edge 10 ns CL 30 pF
```

Every value is now floating free of the column header that gave it
meaning. A retriever might match this chunk to a query about setup time,
but cannot reliably tell you whether "5" is the min, typ, or max — or
even confirm it's nanoseconds and not megahertz, since the unit column
has collapsed into the row.

**Good — Markdown table, column structure intact:**

```markdown
**Table 24 — SPI AC characteristics ($V_{DD}$ = 3.3 V, $T_A$ = 25°C unless noted)**

| Symbol | Parameter | Min | Typ | Max | Unit | Conditions |
|---|---|---|---|---|---|---|
| $f_{SCK}$ | SCK clock frequency, master mode | — | — | 18 | MHz | $C_L$ = 30 pF |
| $t_r$, $t_f$ | SCK rise/fall time | — | — | 8 | ns | $C_L$ = 30 pF |
| $t_{su(MI)}$ | MISO data setup time before SCK edge | 5 | — | — | ns | — |
| $t_{h(MI)}$ | MISO data hold time after SCK edge | 4 | — | — | ns | — |
| $t_{v(MO)}$ | MOSI data valid time after SCK edge | — | — | 10 | ns | $C_L$ = 30 pF |
```

Now a single retrieved row answers "what's the min MISO setup time"
completely and correctly: $t_{su(MI)} \geq 5$ ns, no ambiguity about
which number is which.

---

### 3. Images — linked to reference point, indexed in a manifest

**Bad — images dumped at end of page, disconnected from text:**

```markdown
## Page 12

top surface capacitor has a much higher loop inductance than the bottom
surface capacitor. However, if the board is thick and the cavity is
near the top surface and the cavity is thin, the capacitor on the
bottom will have the higher loop inductance. Figure 13-39 summarizes
three cases.

![Image](./images/img_012_a.png)
![Image](./images/img_012_b.png)
```

The prose mentions "Figure 13-39" but nothing connects that reference to
either image file. If there were three figures on this page instead of
two, there'd be no way to tell which file is which without opening each
one manually.

**Good — image inline at point of reference, captioned, with a manifest entry:**

```markdown
## Page 12 {#page-12}

The top surface capacitor has a much higher loop inductance than the
bottom surface capacitor. However, if the board is thick and the cavity
is near the top surface and the cavity is thin, the capacitor on the
bottom will have the higher loop inductance.

![Figure 13-38: Where should the capacitor go — on the same surface as the BGA or directly under the BGA?](./images/fig_p012_a.png)
*Figure 13-38 — Cross-section showing capacitor placement options:
same-surface mounting (left) versus directly-under mounting (right),
with board thickness $h$ and via separation $s$ labeled.*

<!-- figure-ref: Figure 13-38 -->

Figure 13-39 summarizes three such cases, showing that placing the
capacitor on the bottom can result in a loop inductance on the order
of 2 nH.

![Figure 13-39: Loop inductance comparison for three capacitor-placement cases](./images/fig_p012_b.png)
*Figure 13-39 — Summary of loop inductance for three capacitor-placement
scenarios, showing bottom placement on the order of 2 nH.*

<!-- figure-ref: Figure 13-39 -->
```

…and the corresponding `manifest.json` entry that lets your application
resolve a figure reference to an actual file path without re-parsing the
Markdown:

```json
{
  "figures": {
    "fig_p012_a.png": {
      "page": 12,
      "figure_number": "13-38",
      "caption": "Where should the capacitor go — on the same surface as the BGA or directly under the BGA?",
      "section": "Capacitor Placement Relative to the BGA",
      "path": "images/fig_p012_a.png"
    },
    "fig_p012_b.png": {
      "page": 12,
      "figure_number": "13-39",
      "caption": "Loop inductance comparison for three capacitor-placement cases",
      "section": "Capacitor Placement Relative to the BGA",
      "path": "images/fig_p012_b.png"
    }
  }
}
```

Now a RAG answer that says "see Figure 13-38" can be resolved
programmatically: look up `"13-38"` in the manifest, get
`images/fig_p012_a.png`, serve it from your webserver alongside the
generated answer.

---

### 4. Prose — reconstructed sentences, not OCR line-fragments

**Bad — raw OCR, broken at physical line wraps, hyphenation intact:**

```markdown
At the end of a transmission line with a capac-
itive load, the voltage appears to charge up
with an RC behavior. The C is the capac-
itance of the load. The R is the char-
acteristic impedance of the transmission
line, Z0. The 10-90 rise time for the trans-
mitted signal, if dominated by the RC charg-
ing, is roughly:
```

Every line break is an artifact of the page's physical column width, not
a sentence boundary. Embedded as-is, this chunk reads as eight
disconnected fragments rather than three coherent sentences, and a
similarity search against it performs worse than it should because the
broken words ("capac-itive", "char-acteristic") don't match the whole
words a query would use.

**Good — reconstructed prose, hyphenation rejoined, real sentence and
paragraph boundaries:**

```markdown
At the end of a transmission line with a capacitive load, the voltage
appears to charge up with an RC behavior. The capacitance $C$ is the
capacitance of the load, and the resistance $R$ is the characteristic
impedance of the transmission line, $Z_0$. The 10–90% rise time for the
transmitted signal, if dominated by the RC charging, is roughly:
```

Three complete sentences, properly joined words, and the formula that
follows (not shown here, see Page 1's example) stays attached to the
sentence introducing it rather than floating disconnected.

---

### 5. Chunk self-containment — readable in isolation

**Bad — a chunk that depends on context outside itself:**

```markdown
## Page 47

As mentioned above, the same encoding applies here. The values are
0x1 for the first case and 0x4 for the reset state. This is also true
for the other register.
```

Retrieved alone, this chunk is meaningless: which encoding? Which
register? What does 0x1 vs. 0x4 actually configure? A human or an LLM
seeing only this chunk cannot answer a question about it, even though
the original page made sense in its full reading order.

**Good — same content, restated to be self-contained:**

```markdown
## Page 47 — GPIO Configuration Register (GPIOx_CRL) {#page-47}

Each GPIO pin's mode and speed are configured through a pair of 32-bit
control registers, `GPIOx_CRL` (pins 0–7) and `GPIOx_CRH` (pins 8–15).
Each pin occupies a 4-bit field: 2 bits for mode (`MODE`) and 2 bits for
configuration (`CNF`).

**CNF[1:0] encoding (in output mode):**

| Value | Meaning |
|---|---|
| `00` | General-purpose output, push-pull |
| `01` | General-purpose output, open-drain |
| `10` | Alternate function output, push-pull |
| `11` | Alternate function output, open-drain |

The `MODE0[1:0]` field resets to `0x0` (input mode) and `CNF0[1:0]`
resets to `0x1` (floating input) at power-on, per Table 12. The same
4-bit field pattern repeats for pins 1 through 7 within this register.
```

This version names the register, defines what the bit fields mean, and
states which reset values apply to which field — answerable on its own,
with no dependency on a "this/above/same" reference into a different
chunk that may or may not also be retrieved.

---

<!-- end of guide -->
