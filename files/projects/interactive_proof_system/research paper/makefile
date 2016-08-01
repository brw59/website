# See http://www.math.uiuc.edu/~hildebr/tex/bibliographies.html

FILE = BensResearchPaper

all: one two three four

one: ${FILE}.aux

two: ${FILE}.tex bibliography.bib
	@bibtex $(basename $< .tex)

three: ${FILE}.pdf
	@make -W ${FILE}.tex $^

four: ${FILE}.pdf
	@make -W ${FILE}.tex $^
	@evince $^

${FILE}.aux: ${FILE}.tex
	@pdflatex $^

${FILE}.pdf: ${FILE}.tex bibliography.bib
	@pdflatex $<

clean:
	@rm -f ${FILE}.aux ${FILE}.log ${FILE}.bbl ${FILE}.blg ${FILE}.pdf
