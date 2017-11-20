;;--------------------General--------------------
(global-set-key (kbd "M-n") 'forward-paragraph)
(global-set-key (kbd "M-p") 'backward-paragraph)
(global-set-key (kbd "C-`") 'set-mark-command)
(global-set-key (kbd "<f5>") 'eshell)
;; 修改透明度
(set-frame-parameter (selected-frame) 'alpha (list 78 78))
(add-to-list 'default-frame-alist (cons 'alpha (list 78 78)))
;; set the cursor
(setq-default cursor-type 'bar)
;; comment-dwim
(defun strong-comment-dwim-line (&optional arg)
  "Replacement for the comment-dwim command. If no region is selected and current line is not blank and we are not at the end of the line, then comment current line. Replaces default behaviour of comment-dwim, when it inserts comment at the end of the line."
  (interactive "*P")
  (comment-normalize-vars)
  (if (and (not (region-active-p)) (not (looking-at "[ \t]*$")))
      (comment-or-uncomment-region (line-beginning-position) (line-end-position))
    (comment-dwim arg)))
(global-set-key (kbd "M-;") 'strong-comment-dwim-line) 
;; Remove tool bar
(tool-bar-mode -1)
;; 不要滚动栏，现在都用滚轴鼠标了，可以不用滚动栏了
(scroll-bar-mode -1)
;; 设置行号
(global-linum-mode t)
;; Change the Title
(setq frame-title-format "%b@lmxyy'-emacs")
;; 滚动页面时比较舒服，不要整页的滚动
(setq scroll-step 1
      scroll-margin 3
      scroll-conservatively 10000)
;; 设置界面 start
(if window-system
    (setq default-frame-alist
	  (append
	   '( (top . 0)
	      (left . 0)
	      (width . 300)
	      (height . 300))
	   default-frame-alist))
  )
;; 允许emacs和外部其他程序的粘贴
(setq x-select-enable-clipboard t)
;; 去掉菜单栏，我将F10绑定为显示菜单栏，万一什么东西忘了，需要菜单栏了可以摁F10调出，再摁F10就去掉菜单
(menu-bar-mode -1)
;; 显示列号
(setq column-number-mode t)
;; 开启语法高亮。
(global-font-lock-mode 1)
;; Auto Indent
(global-set-key (kbd "RET") 'newline-and-indent)


;; --------------------Tex Mode--------------------
;; Emacs加载Auctex
(load "auctex.el" nil t t)
(load "preview-latex.el" nil t t)
(setq TeX-auto-save t)
(setq TeX-parse-self t)
(setq-default TeX-master nil)	    
(add-hook 'LaTeX-mode-hook
	  '(lambda ()
	     ;;LaTeX 模式下，不打开自动折行
	     (turn-off-auto-fill)
	     ;; ;; 打开自动补全
	     ;; (auto-complete-mode 1)
	     ;; 启动 math mode，你也可以不用。
	     (LaTeX-math-mode 1)
	     ;; 打开 outline mode
	     (outline-minor-mode 1)
	     ;; 接下来是和编译 TeX 有关的
	     ;; 编译的时候，不在当前窗口中显示编译信息
	     (setq TeX-show-compilation nil)
	     (setq TeX-clean-confirm nil)
	     (setq TeX-save-query nil)
	     ;; 按 \ 后光标跳到 mini-buffer 里面输入命令
	     ;; 看个人习惯，因为如果有了 auto-complete 和 yasnippet
	     ;; 这个不开启也问题不大。
	     (setq TeX-electric-escape t)
	     ;; 重新定义 pdf viewer，我设定为了 evince。
	     (setq TeX-view-program-list '(("Evince" "evince %o")))
	     (setq TeX-view-program-selection
	     	   '((output-pdf "Evince")))
	     ;; 设置编译引擎为 XeTeX
	     (setq TeX-global-PDF-mode t
	     	   TeX-engine 'xetex)
	     ;; 使用 XeLaTeX 作为默认程序来编译 LaTeX
	     (add-to-list 'TeX-command-list
	     		    '("XeLaTeX" "%'xelatex%(mode)%' %t"
	     				     TeX-run-TeX nil t))
	     (setq TeX-command-default "XeLaTeX")
	     ;; 设置编译信息
	     (defun compile-xelatex ()
	       (interactive)
	       (compile (format "xelatex -shell-escape %s" (buffer-name))))
	     (global-set-key (kbd "<f9>") 'compile-xelatex)
	     (defun compile-latex ()
	       (interactive)
	       (compile (format "latex -shell-escape %s" (buffer-name))))
	     (global-set-key (kbd "C-<f9>") 'compile-latex)
	     ;; 设置tab为4个空格的宽度	 
	     ;; (setq c-basic-offset 4)
	     ;; (setq default-tab-width 4)
	     )
	  )

;; --------------------C++ Mode--------------------
(add-hook 'c++-mode-hook
	  '(lambda ()
	     ;; 设置编译信息
	     (defun compile-cpp ()
	       (interactive)
	       (compile (format "g++ -o %s %s -g -lm -Wall -std=c++11"  (file-name-sans-extension (buffer-name))(buffer-name))))
	     (defun compile-cpp-O2 ()
	       (interactive)
	       (compile (format "g++ -o %s %s -g -lm -Wall -std=c++11 -O2"  (file-name-sans-extension (buffer-name))(buffer-name))))
	     (global-set-key (kbd "<f9>") 'compile-cpp)
	     (global-set-key (kbd "C-<f9>") 'compile-cpp-O2)
	     ;; 设置一键调试
	     (global-set-key (kbd "<f8>") 'gud-gdb)
	     ;; 设置tab为4个空格的宽度	 
	     (setq c-basic-offset 4)
	     (setq default-tab-width 4)
	     )
	  )

;; --------------------Java Mode--------------------
(add-hook 'java-mode-hook
	  '(lambda ()
	     ;; 设置编译信息
	     (defun compile-java ()
	       (interactive)
	       (compile (format "javac %s" (buffer-name))))
	     (global-set-key (kbd "<f9>") 'compile-java)
	     ;; 设置tab为4个空格的宽度	 
	     (setq c-basic-offset 4)
	     (setq default-tab-width 4)
	     )
	  )


;; --------------------Org Mode--------------------
(setq org-startup-indented t)


;; --------------------Ido Mode--------------------
;; 启用ido模式
(ido-mode t)

;; --------------------Verilog Mode--------------------
(add-hook 'verilog-mode-hook
	  (lambda ()
	    ;; 设置编译信息
	    (defun compile-verilog ()
	      (interactive)
	      (compile (format "iverilog -o %s %s"  (file-name-sans-extension (buffer-name))(buffer-name))))
	    (global-set-key (kbd "<f9>") 'compile-verilog)
	    )
	  )

;; --------------------Custon Sets--------------------
(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(column-number-mode t)
 '(cua-mode t nil (cua-base))
 '(inhibit-startup-screen t)
 '(menu-bar-mode nil)
 '(tool-bar-mode nil))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(default ((t (:family "Courier 10 Pitch" :foundry "bitstream" :slant normal :weight bold :height 151 :width normal)))))
