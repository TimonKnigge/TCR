all:	tcr
tcr:
	@pdflatex tcr.tex
clean:
	@rm -f tcr.aux
	@rm -f tcr.toc
	@rm -f tcr.out
	@rm -f tcr.log
	@rm -f tcr.pdf
