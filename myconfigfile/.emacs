(global-linum-mode 1)

;;color theme
;;(require 'color-theme)
;;(color-theme-gnome2)

;;session
;;(add-to-list 'load-path "/usr/share/emacs/extension/")
;;(require 'session)
;;  (add-hook 'after-init-hook 'session-initialize)

(load "desktop") 
(desktop-load-default) 
(desktop-read)

(require 'ibuffer)
(global-set-key (kbd "C-x C-b") 'ibuffer)

(require 'ido)
(ido-mode t)

;;swbuff
(add-to-list 'load-path "~/.emacs.d/extension")
(require 'swbuff)
(global-set-key (kbd "") 'swbuff-switch-to-previous-buffer)
(global-set-key (kbd "") 'swbuff-switch-to-next-buffer)
(setq swbuff-exclude-buffer-regexps 
     '("^ " "\\*.*\\*"))
(setq swbuff-status-window-layout 'scroll)
(setq swbuff-clear-delay 1)
(setq swbuff-separator "|")
(setq swbuff-window-min-text-height 1)

(require 'tabbar)
(tabbar-mode)
(global-set-key [s-up] 'tabbar-backward-group)
(global-set-key [s-down] 'tabbar-forward-group)
(global-set-key (kbd "C-:") 'tabbar-backward)
(global-set-key (kbd "C-\"") 'tabbar-forward)

(require 'recentf)
(recentf-mode 1)
(defun recentf-open-files-compl ()
  (interactive)
  (let* ((all-files recentf-list)
     (tocpl (mapcar (function 
	     (lambda (x) (cons (file-name-nondirectory x) x))) all-files))
     (prompt (append '("File name: ") tocpl))
     (fname (completing-read (car prompt) (cdr prompt) nil nil)))
    (find-file (cdr (assoc-ignore-representation fname tocpl))))) 
(global-set-key [(control x)(control r)] 'recentf-open-files-compl)

(global-set-key [(meta ?/)] 'hippie-expand)
(setq hippie-expand-try-functions-list 
      '(try-expand-dabbrev
    try-expand-dabbrev-visible
    try-expand-dabbrev-all-buffers
    try-expand-dabbrev-from-kill
    try-complete-file-name-partially
    try-complete-file-name
    try-expand-all-abbrevs
    try-expand-list
    try-expand-line
    try-complete-lisp-symbol-partially
    try-complete-lisp-symbol))

;;mark
(global-set-key (kbd "M-.") 'ska-point-to-register)
(global-set-key (kbd "M-,") 'ska-jump-to-register)
(defun ska-point-to-register()
  "Store cursorposition _fast_ in a register. 
Use ska-jump-to-register to jump back to the stored 
position."
  (interactive)
  (setq zmacs-region-stays t)
  (point-to-register 8))

(defun ska-jump-to-register()
  "Switches between current cursorposition and position
that was stored with ska-point-to-register."
  (interactive)
  (setq zmacs-region-stays t)
  (let ((tmp (point-marker)))
        (jump-to-register 8)
	(set-register 8 tmp)))

(defun wy-go-to-char (n char)
  "Move forward to Nth occurence of CHAR.
Typing `wy-go-to-char-key' again will move forwad to the next Nth
occurence of CHAR."
  (interactive "p\ncGo to char: ")
  (search-forward (string char) nil nil n)
  (while (char-equal (read-char)
	     char)
    (search-forward (string char) nil nil n))
  (setq unread-command-events (list last-input-event)))
(define-key global-map (kbd "C-c f") 'wy-go-to-char)

(require 'ctypes)
(ctypes-auto-parse-mode 1)

;;simple happy config
(setq visible-bell t)
(setq inhibit-startup-message t)
(setq column-number-mode t) 
(setq mouse-yank-at-point t)
(setq kill-ring-max 200)
(setq default-fill-column 80)
(setq scroll-margin 3
      scroll-conservatively 10000)
(show-paren-mode t)
(setq show-paren-style 'parentheses)
(mouse-avoidance-mode 'animate)
(setq frame-title-format "emacs@%b")
(auto-image-file-mode)
(global-font-lock-mode t)
(put 'set-goal-column 'disabled nil)
(put 'narrow-to-region 'disabled nil)
(put 'upcase-region 'disabled nil)
(put 'downcase-region 'disabled nil)
(put 'LaTeX-hide-environment 'disabled nil)
(setq user-full-name "Airead Fan")
(setq user-mail-address "fgh1987168@gmail.com")

(global-set-key [(f5)] 'gud-go)
(add-hook 'gdb-mode-hook '(lambda ()
	        (define-key c-mode-base-map [(f5)] 'gud-go)
                            (define-key c-mode-base-map [(f7)] 'gud-step)
                            (define-key c-mode-base-map [(f8)] 'gud-next)))

;;linux kernel style
(defun linux-c-mode ()
  "C mode with adjusted defaults for use with the Linux kernel."
  (interactive)
  (c-mode)
  (c-set-style "K&R")
  (setq tab-width 4)
  (setq indent-tabs-mode nil)
  (setq c-basic-offset 4))
(add-to-list 'auto-mode-alist '("\.c$" . linux-c-mode))
(add-to-list 'auto-mode-alist '("\.h$" . linux-c-mode))

;; C++ mode
(defun linux-cpp-mode ()
  "C++ mode with adjusted defaults for use with the Linux kernel."
  (interactive)
  (c++-mode)
  (c-set-style "K&R")
  (setq tab-width 8)
  (setq indent-tabs-mode t)
  (setq c++-basic-offset 8))
(add-to-list 'auto-mode-alist '("\.cpp$" . linux-cpp-mode))

;; smart compile
(add-to-list 'load-path "~/.emacs.d/extension" t)
(require 'smart-compile+)
(global-set-key (kbd "<f9>") 'smart-compile)
(put 'dired-find-alternate-file 'disabled nil)

;; orgmode
(add-to-list 'load-path "/home/airead/org") 
 (require 'org)                                   
;; (add-to-list 'auto-mode-alist '("\\.org$" . org-mode))
 (add-hook 'org-mode-hook 'turn-on-font-lock);;ont need when global-font-lock-mode is on
 (define-key global-map "\C-cl" 'org-store-link)
 (define-key global-map "\C-ca" 'org-agenda)
 (define-key global-map "\C-cb" 'org-iswitchb)
 (setq org-log-done t) 
;;自动换行
(add-hook 'org-mode-hook
    (lambda () (setq truncate-lines nil)))
(setq default-input-method "TeX")

;;CEDET
(add-to-list 'load-path "~/.emacs.d/cedet-1.0.1/common" t)
(require 'cedet)
(require 'semantic-ia)
(semantic-load-enable-minimum-features)
(semantic-load-enable-code-helpers)
;;(semantic-load-enable-semantic-debugging-helpers)
;;(semantic-load-enable-guady-code-helpers)
;;(semantic-load-enable-excessive-code-helpers)

(global-set-key (kbd "M-n") 'semantic-ia-complete-symbol-menu)

(setq comment-style 'multi-line)


(defun insert-main ()
  "Insert head and main"
  (interactive)
  (insert "#include <stdio.h>\n#include <string.h>\n#include <stdlib.h>
#include <errno.h>\n#include <fcntl.h>\n#include <unistd.h>
#include <sys/types.h>\n#include <sys/stat.h>\n\nint main(int argc, char *argv[])
{\n\n}")
  (backward-char 2)
)
(global-set-key (kbd "C-c m") 'insert-main)

(global-set-key (kbd "M-]") 'delete-blank-lines)



(defun insert-author ()
  "Insert author and date"
  (interactive)
  (insert "/********************************************************\n")
  (insert " * @author  Airead Fan <fgh1987168@gmail.com>\t\t*\n")
  (insert " * @date    ")
  (insert (format-time-string "%Y%b %d %H:%M:%S %Z\t\t\t*" (current-time)))
  (insert "\n")
  (insert " ********************************************************\n")
  (insert " *\t\tafter studying C ")
  (insert (format "%d " (- (time-to-days (current-time)) (time-to-days (encode-time 0 0 0 18 7 2011 +0800)))))
  (insert "days\t\t*\n")
  (insert " *\t\tafter studying APUE ")
  (insert (format "%d " (- (time-to-days (current-time)) (time-to-days (encode-time 0 0 0 22 8 2011 +0800)))))
  (insert "days\t\t*\n")
  (insert " *\t\tafter studying ARM ")
  (insert (format "%d " (- (time-to-days (current-time)) (time-to-days (encode-time 0 0 0 8 10 2011 +0800)))))
  (insert "days\t\t*\n")

  (insert " ********************************************************/\n")
  (insert "\n/*\n")
  (insert " * This program is free software; you can redistribute it and/or modify\n")
  (insert " * it under the terms of the GNU General Public License as published by\n")
  (insert " * the Free Software Foundation; either version 2 of the License, or\n")
  (insert " * (at your option) any later version.\n")
  (insert " *\n")
  (insert " * This program is distributed in the hope that it will be useful,\n")
  (insert " * but WITHOUT ANY WARRANTY; without even the implied warranty of\n")
  (insert " * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n")
  (insert " * GNU General Public License for more details.\n")
  (insert " *\n")
  (insert " * You should have received a copy of the GNU General Public License\n")
  (insert " * along with this program; if not, write to the Free Software\n")
  (insert " * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA\n")
  (insert " */\n")
 )
(global-set-key (kbd "C-c c") 'insert-author)

(defun insert-author ()
  "Insert author and date"
  (interactive)
  (insert "/**\n")
  (insert " * @file ")
  (insert (buffer-name))
  (insert "\n")
  (insert " * @brief \n")
  (insert " * @author Airead Fan <fgh1987168@gmail.com>\n")
  (insert " * @date ")
;;  (insert (format-time-string "%Y %b %d %H:%M:%S %Z\n" (current-time)))
  (insert (format-time-string "%Y/%m/%d %T\n" (current-time)))
  (insert " */")
  (insert "\n")
 )

(defun insert-current-date ()
  "insert current date"
  (interactive)
  (insert (format-time-string "%Y/%m/%d %T\n" (current-time))))
(global-set-key (kbd "C-c d") 'insert-current-date)


(defun insert-function-describe ()
  "Insert author and date"
  (interactive)
  (insert "/**\n")
  (insert " * @brief \n")
  (insert " * @param \n");
  (insert " * @return \n")
  (insert " */")
  (insert "\n")
 )
(global-set-key (kbd "C-c f") 'insert-function-describe)

;; highlight
(add-to-list 'load-path "~/.emacs.d/extension")
(require 'highlight-symbol)
;; highlight
(load-file "~/.emacs.d/extension/highlight-symbol.el")
(global-set-key (kbd "C-'") 'highlight-symbol-at-point)
(global-set-key (kbd "C-M-'") 'highlight-symbol-remove-all)
(global-set-key (kbd "C-,") 'highlight-symbol-prev)
(global-set-key (kbd "C-.") 'highlight-symbol-next)

;;Highlight #if 0 to #endif
(defun my-c-mode-font-lock-if0 (limit)
  (save-restriction
    (widen)
    (save-excursion
      (goto-char (point-min))
      (let ((depth 0) str start start-depth)
        (while (re-search-forward "^\\s-*#\\s-*\\(if\\|else\\|endif\\)" limit 'move)
          (setq str (match-string 1))
          (if (string= str "if")
              (progn
                (setq depth (1+ depth))
                (when (and (null start) (looking-at "\\s-+0"))
                  (setq start (match-end 0)
                        start-depth depth)))
            (when (and start (= depth start-depth))
              (c-put-font-lock-face start (match-beginning 0) 'font-lock-comment-face)
              (setq start nil))
            (when (string= str "endif")
              (setq depth (1- depth)))))
        (when (and start (> depth 0))
          (c-put-font-lock-face start (point) 'font-lock-comment-face)))))
  nil)

(defun my-c-mode-common-hook ()
  (font-lock-add-keywords
   nil
   '((my-c-mode-font-lock-if0 (0 font-lock-comment-face prepend))) 'add-to-end))

(add-hook 'c-mode-common-hook 'my-c-mode-common-hook)
;;Highlight end


;(add-to-list 'load-path "/usr/share/emacs/extension/" t)
;(require 'silentcomp)
;;ECB
(add-to-list 'load-path "~/.emacs.d/ecb-2.40" t)
(require 'ecb-autoloads)


;;xcscope
(require 'xcscope)
(define-key global-map [(control f3)]  'cscope-set-initial-directory)
(define-key global-map [(control f4)]  'cscope-unset-initial-directory)
(define-key global-map [(control f5)]  'cscope-find-this-symbol)
(define-key global-map [(control f6)]  'cscope-find-global-definition)
(define-key global-map [(control f7)]  'cscope-find-global-definition-no-prompting)
(define-key global-map [(control f8)]  'cscope-pop-mark)
;;	(define-key global-map [(control f9)]  'cscope-next-symbol)
;;	(define-key global-map [(control f10)] 'cscope-next-file)
;;	(define-key global-map [(control f11)] 'cscope-prev-symbol)
;;	(define-key global-map [(control f12)] 'cscope-prev-file)
;;      (define-key global-map [(meta f9)]  'cscope-display-buffer)
;;      (defin-ekey global-map [(meta f10)] 'cscope-display-buffer-toggle)

;;;  ;;docbook
;;;  ;;; set outline mode
;;;  (setq outline-minor-mode-prefix [(control o)])
;;;  (setq outline-minor-mode-prefix [(kbd "C-o")])
;;;  (require 'docbook-xml-mode)
;;;  (add-hook 'docbook-xml-mode-hook 
;;;  	  (function (lambda ()
;;;  		      (setq outline-regexp "^.*<!\\-\\-\\*+") 
;;;  		      (outline-minor-mode)
;;;   		      (hide-body))))
;;;  
;;;  (defun format-screen-code (start end)
;;;    "Replace “<” to “&lt;” and other chars in HTML.
;;;  This works on the current region."
;;;    (interactive "r")
;;;    (save-restriction 
;;;      (narrow-to-region start end)
;;;      (goto-char (point-min))
;;;      (while (search-forward "&" nil t) (replace-match "&amp;" nil t))
;;;      (goto-char (point-min))
;;;      (while (search-forward "<" nil t) (replace-match "&lt;" nil t))
;;;      (goto-char (point-min))
;;;      (while (search-forward ">" nil t) (replace-match "&gt;" nil t))
;;;  ;    (goto-char (point-min))
;;;  ;   (while (search-forward-regexp "^ *[^0-9A-Za-z\\\*]" nil t) (replace-match "" nil t))
;;;      )
;;;    )
;;;  (global-set-key (kbd "C-c t") 'format-screen-code)
;;;  
(add-to-list 'load-path "/usr/share/auto-complete")
; Load the default configuration
(require 'auto-complete-config)
; Make sure we can find the dictionaries
(add-to-list 'ac-dictionary-directories "/usr/share/auto-complete/dict")
; Use dictionaries by default
(setq-default ac-sources (add-to-list 'ac-sources 'ac-source-dictionary))
(global-auto-complete-mode t)
; Start auto-completion after 2 characters of a word
(setq ac-auto-start 2)
; case sensitivity is important when finding matches
(setq ac-ignore-case nil)

;; Emacs muse
(require 'muse-mode)

(require 'muse-html)         ;添加html格式的支持
(require 'muse-latex)        ; 添加latex格式的支持
(require 'muse-texinfo)      ; 添加texinfo格式的支持
(require 'muse-docbook)      ; 添加docbook格式的支持
;; (require 'muse-wiki nil t)   
(require 'muse-project)      ; 添加wiki project的支持

;设置编码方式为utf-8
(setq muse-html-meta-content-type (concat "text/html; charset=utf-8"))
(setq muse-html-style-sheet "<link rel='stylesheet' type='text/css' charset='utf-8' media='all' href='../css/core.css' />")

;新建一个wiki工程
(setq muse-project-alist
      '(("WorkWiki"
         ("~/study/muse/WorkWiki" :default "index")
         (:base "html" :path "~/study/muse/publish"))))

;; yasnippet
(setq yas/trigger-key "C-;")
(setq yas/root-directory "~/.emacs.d/snippets")
(yas/load-directory yas/root-directory)
(setq-default mode-require-final-newline nil)

;; bind-key
(global-set-key (kbd "C-x r u") 'string-insert-rectangle)

;; markdown
(autoload 'markdown-mode "markdown-mode.el"
   "Major mode for editing Markdown files" t)
(setq auto-mode-alist
   (cons '("\\.markdown" . markdown-mode) auto-mode-alist))

;; default brower
(setq browse-url-generic-program (executable-find "google-chrome")
      browse-url-browser-function 'browse-url-generic)
;;(global-set-key (kbd "C-x p") 'browse-url-at-point)

;; pymacs
(autoload 'pymacs-apply "pymacs")
(autoload 'pymacs-call "pymacs")
(autoload 'pymacs-eval "pymacs" nil t)
(autoload 'pymacs-exec "pymacs" nil t)
(autoload 'pymacs-load "pymacs" nil t)
(autoload 'pymacs-autoload "pymacs")

;; ropemacs
(pymacs-load "ropemacs" "rope-")

;; pylookup
;; add pylookup to your loadpath, ex) "~/.lisp/addons/pylookup"
(setq pylookup-dir "~/.emacs.d/pylookup")
(add-to-list 'load-path pylookup-dir)
;; load pylookup when compile time
(eval-when-compile (require 'pylookup))

;; set executable file and db file
(setq pylookup-program (concat pylookup-dir "/pylookup.py"))
(setq pylookup-db-file (concat pylookup-dir "/pylookup.db"))

;; to speedup, just load it on demand
(autoload 'pylookup-lookup "pylookup"
  "Lookup SEARCH-TERM in the Python HTML indexes." t)
(autoload 'pylookup-update "pylookup" 
  "Run pylookup-update and create the database at `pylookup-db-file'." t)

;; set font
(add-to-list 'default-frame-alist '(font . "monaco"))

;; flymake
;;(autoload 'flymake-find-file-hook "flymake" "" t)
;;(add-hook 'find-file-hook 'flymake-find-file-hook)
;;(setq flymake-gui-warnings-enabled nil)
;;(setq flymake-log-level 0)

;; new python mode
(add-to-list 'load-path "~/.emacs.d/extension/python.el")
(require 'python)

(global-set-key (kbd "<M-f7>") 'rope-goto-definition)
(global-set-key (kbd "<M-f8>") 'rope-pop-mark)

;; auto-complete for python
;;(autoload 'python-mode "python-mode" "Python Mode." t)
(add-to-list 'auto-mode-alist '("\\.py\\'" . python-mode))
(add-to-list 'interpreter-mode-alist '("python" . python-mode))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;                                         
;;; Auto-completion                                                                                            
;;;  Integrates:                                                                                               
;;;   1) Rope                                                                                                  
;;;   2) Yasnippet                                                                                             
;;;   all with AutoComplete.el                                                                                 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;                                         
(defun prefix-list-elements (list prefix)
  (let (value)
    (nreverse
     (dolist (element list value)
      (setq value (cons (format "%s%s" prefix element) value))))))
(defvar ac-source-rope
  '((candidates
     . (lambda ()
         (prefix-list-elements (rope-completions) ac-target))))
  "Source for Rope")
(defun ac-python-find ()
  "Python `ac-find-function'."
  (require 'thingatpt)
  (let ((symbol (car-safe (bounds-of-thing-at-point 'symbol))))
    (if (null symbol)
        (if (string= "." (buffer-substring (- (point) 1) (point)))
            (point)
          nil)
      symbol)))
(defun ac-python-candidate ()
  "Python `ac-candidates-function'"
  (let (candidates)
    (dolist (source ac-sources)
      (if (symbolp source)
          (setq source (symbol-value source)))
      (let* ((ac-limit (or (cdr-safe (assq 'limit source)) ac-limit))
             (requires (cdr-safe (assq 'requires source)))
             cand)
        (if (or (null requires)
                (>= (length ac-target) requires))
            (setq cand
                  (delq nil
                        (mapcar (lambda (candidate)
                                  (propertize candidate 'source source))
                                (funcall (cdr (assq 'candidates source)))))))
        (if (and (> ac-limit 1)
                 (> (length cand) ac-limit))
            (setcdr (nthcdr (1- ac-limit) cand) nil))
        (setq candidates (append candidates cand))))
    (delete-dups candidates)))
(add-hook 'python-mode-hook
          (lambda ()
                 (auto-complete-mode 1)
                 (set (make-local-variable 'ac-sources)
                      (append ac-sources '(ac-source-rope) '(ac-source-yasnippet)))
                 (set (make-local-variable 'ac-find-function) 'ac-python-find)
                 (set (make-local-variable 'ac-candidate-function) 'ac-python-candidate)
                 (set (make-local-variable 'ac-auto-start) nil)))

;;Ryan's python specific tab completion                                                                        
(defun ryan-python-tab ()
  ; Try the following:                                                                                         
  ; 1) Do a yasnippet expansion                                                                                
  ; 2) Do a Rope code completion                                                                               
  ; 3) Do an indent                                                                                            
  (interactive)
  (if (eql (ac-start) 0)
      (indent-for-tab-command)))

(defadvice ac-start (before advice-turn-on-auto-start activate)
  (set (make-local-variable 'ac-auto-start) t))
(defadvice ac-cleanup (after advice-turn-off-auto-start activate)
  (set (make-local-variable 'ac-auto-start) nil))

;; (define-key python-mode-map "\t" 'ryan-python-tab)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;                                         
;;; End Auto Completion                                                                                        
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


(custom-set-variables
  ;; custom-set-variables was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(ecb-options-version "2.40")
 '(safe-local-variable-values (quote ((lexical-binding . t))))
 '(session-use-package t nil (session))
 '(text-mode-hook (quote (turn-on-flyspell turn-on-auto-fill text-mode-hook-identify))))
(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 )
