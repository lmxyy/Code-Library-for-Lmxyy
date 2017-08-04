(global-set-key (kbd "M-]") 'forward-paragraph)
(global-set-key (kbd "M-[") 'backward-paragraph)
(global-set-key (kbd "<f12>" 'print-buffer)
;;;;;启用ido模式
(ido-mode t)
;;;;;去掉工具栏
(tool-bar-mode -1)
;;;;;不要滚动栏，现在都用滚轴鼠标了，可以不用滚动栏了
(scroll-bar-mode -1)
;;;;;设置行号
(global-linum-mode t)
;;;;;设置编译信息
(defun compile-file ()
  (interactive)
  (compile (format "g++ -o %s %s -g -lm -Wall -std=c++11"  (file-name-sans-extension (buffer-name))(buffer-name))))
(global-set-key (kbd "<f9>") 'compile-file)
;;;;;设置一键调试
(global-set-key (kbd "<f8>") 'gud-gdb)
;;;;;改变emacs标题栏的标题
(setq frame-title-format "%b@lmxyy'-emacs")
;;;;;允许emacs和外部其他程序的粘贴
(setq x-select-enable-clipboard t)
;;;;;去掉菜单栏，我将F10绑定为显示菜单栏，万一什么东西忘了，需要菜单栏了可以摁F10调出，再摁F10就去掉菜单
(menu-bar-mode -1)
;; 显示列号
(setq column-number-mode t)
;;开启语法高亮。
(global-font-lock-mode 1)
;;设置tab为2个空格的宽度
(setq default-tab-width 4)
(setq c-basic-offset 4)
;;;;;;;;;  设置界面 start
(if window-system
        (setq default-frame-alist
                (append
                        '( (top . 0)
                                 (left . 0)
                                             (width . 300)
                                             (height . 300))
                                                                  default-frame-alist))
)
;;;启动最大化
;;;(setq initial-frame-alist '((top . 0) (left . 0) (width . 970) (height . 490)))
;;;;;修改透明度
(set-frame-parameter (selected-frame) 'alpha (list 78 78))
(add-to-list 'default-frame-alist (cons 'alpha (list 78 78)))
(setq-default cursor-type 'bar)
;;;;;滚动页面时比较舒服，不要整页的滚动
(setq scroll-step 1
        scroll-margin 3
        scroll-conservatively 10000)
;;;;;使用C-k删掉指针到改行末的所有东西
;;;;;(setq-default kill-whole-line t)
;;;;;设置org模式
(setq org-startup-indented t)
(global-set-key (kbd "RET") 'newline-and-indent)
(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(column-number-mode t)
 '(inhibit-startup-screen t)
 '(menu-bar-mode nil)
 '(tool-bar-mode nil))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(default ((t (:family "Courier 10 Pitch" :foundry "bitstream" :slant normal :weight bold :height 151 :width normal)))))
