;; Default Font: Courier 10 Pitch Bold    Size: 15
;; Remember to set CUA-mode and save your options.
(global-set-key (kbd "M-n") 'forward-paragraph)
(global-set-key (kbd "M-p") 'backward-paragraph)
(global-set-key (kbd "RET") 'newline-and-indent)
(global-set-key (kbd "<f8>") 'gud-gdb)
(defun compile-cpp ()
  (interactive)
  (compile (format "g++ -o %s %s -g -lm -Wall -std=c++11"  (file-name-sans-extension (buffer-name))(buffer-name))))
(global-set-key (kbd "<f9>") 'compile-cpp)
(global-linum-mode t)
(setq default-tab-width 4)
(setq c-basic-offset 4)
