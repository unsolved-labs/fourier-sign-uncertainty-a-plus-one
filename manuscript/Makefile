LATEXMK ?= latexmk
SOURCE := r012_fourier_sign_uncertainty.tex
PDF := r012_fourier_sign_uncertainty.pdf

.PHONY: all clean
all: $(PDF)

$(PDF): $(SOURCE)
	$(LATEXMK) -pdf -interaction=nonstopmode -halt-on-error $(SOURCE)

clean:
	$(LATEXMK) -C $(SOURCE)
