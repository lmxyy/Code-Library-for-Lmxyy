compile_tex:
	@xelatex --shell-escape template.tex
	evince template.pdf
