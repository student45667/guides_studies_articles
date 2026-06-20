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
| What are ideal materials for RAG with minimal loss? — a guide to converting technical PDFs (formulas, tables, images) into RAG-ready documents without information loss | [rag_minimal_loss_guide.md](./rag_minimal_loss_guide.md) | [rag_minimal_loss_guide.html](./rag_minimal_loss_guide.html) *(open in browser for the interactive version)* |

## How to read

- **Markdown files** render directly on GitHub/GitLab, or open in any
  editor — these are also the canonical RAG-ready source, formatted per
  the conventions described in the RAG guide itself (LaTeX formulas,
  real Markdown tables, captioned inline images, self-contained sections).
- **HTML files** are standalone interactive documents — download or
  clone the repo and open the `.html` file directly in a browser
  (double-click, or `open rag_minimal_loss_guide.html` on macOS) for
  toggleable comparisons, KaTeX-rendered formulas, and scroll navigation.
  They require an internet connection on first load to fetch fonts and
  the KaTeX renderer from CDN.

## Topics covered so far

- Converting technical PDFs (datasheets, scope manuals, engineering
  textbooks) to RAG-ready Markdown with minimal information loss
- Why classic OCR fails on formulas and tables, and when to route to
  vision-based transcription instead
- Hybrid extraction pipelines for large documents (cost-aware routing)
- Chunking strategy and structure for technical-document RAG

More studies will be added here as they're written.

---

<!-- repo: guides_studies_articles -->
<!-- maintained by: Alex Chiomny -->
