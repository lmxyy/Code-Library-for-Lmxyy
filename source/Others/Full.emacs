;;--------------------General--------------------
(global-set-key (kbd "M-n") 'forward-paragraph)
(global-set-key (kbd "M-p") 'backward-paragraph)
(global-set-key (kbd "<f12>") 'print-buffer)
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
(setq Tex-auto-save t)
(setq Tex-parse-self t)
(setq-default Tex-master nil)
;; 设置编译信息
(defun compile-xelatex ()
  (interactive)
  (compile (format "xelatex -shell-escape %s" (buffer-name))))
(global-set-key (kbd "<f6>") 'compile-xelatex)
(defun compile-latex ()
  (interactive)
  (compile (format "latex -shell-escape %s" (buffer-name))))
(global-set-key (kbd "C-<f6>") 'compile-latex)

;; --------------------C++ Mode--------------------
;; 设置编译信息
(defun compile-cpp ()
  (interactive)
  (compile (format "g++ -o %s %s -g -lm -Wall -std=c++11"  (file-name-sans-extension (buffer-name))(buffer-name))))
(global-set-key (kbd "<f9>") 'compile-cpp)
(defun compile-cpp-O2 ()
  (interactive)
  (compile (format "g++ -o %s %s -g -lm -Wall -std=c++11 -O2"  (file-name-sans-extension (buffer-name))(buffer-name))))
(global-set-key (kbd "C-<f9>") 'compile-cpp-O2)
;; 设置一键调试
(global-set-key (kbd "<f8>") 'gud-gdb)
;; 设置tab为4个空格的宽度
(setq c-basic-offset 4)
(setq default-tab-width 4)

;; --------------------Java Mode--------------------
;; 设置编译信息
(defun compile-java ()
  (interactive)
  (compile (format "javac %s" (buffer-name))))
(global-set-key (kbd "<f7>") 'compile-java)

;; --------------------Org Mode--------------------
(setq org-startup-indented t)
;; The following lines are always needed. Choose your own keys.
(add-to-list 'auto-mode-alist '("\\.org\\'" . org-mode))
(add-hook 'org-mode-hook 'turn-on-font-lock) ; not needed when global-font-lock-mode is on
(global-set-key "\C-cl" 'org-store-link)
(global-set-key "\C-ca" 'org-agenda)
(global-set-key "\C-cb" 'org-iswitchb)
;; Auto-line-breaking
;; 这一句定义一个函数
(defun my-org-mode()  (setq truncate-lines nil))
;; 把这个函数加入到`org-mode-hook'中，这样每次打开org文件时都会先执行这个函数
(add-hook 'org-mode-hook 'my-org-mode)

;; --------------------Ido Mode--------------------
;; 启用ido模式
(ido-mode t)

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
