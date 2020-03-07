
---
##### String Utils 
<a id="inline-stdstring-qqconst-stdstring-s"></a>
##### inline std::string qq(const std::string&amp; s) 
###### *Param:* s 
###### *Return:*  
<a id="inline-stdstring-chopconst-stdstring-s"></a>
##### inline std::string chop(const std::string&amp; s) 
###### *Param:* s 
###### *Return:*  
<a id="inline-stdstring-chopconst-stdstring-s-const-stdstring-chopped"></a>
##### inline std::string chop(const std::string&amp; s, const std::string&amp; chopped) 
###### *Param:* s 
###### *Param:* chopped 
###### *Return:*  
<a id="t-toconst-stdstring-source"></a>
##### T to(const std::string&amp; source) 
###### *Param:* source 
###### *Return:*  

---

---
##### Container Utils 
<a id="bool-containsconst-t-container-const-stdstring-s"></a>
##### bool contains(const T&amp; container, const std::string&amp; s) 
###### *Param:* container 
###### *Param:* s 
###### *Return:*  
<a id="stdoptionalt-atconst-c-container-const-stdstring-s-unsigned-index-0"></a>
##### std::optional&lt;T&gt; at(const C&amp; container, const std::string&amp; s, unsigned index = 0) 
###### *Param:* container 
###### *Param:* s 
###### *Param:* index 
###### *Return:*  
<a id="t-atorconst-c-container-const-stdstring-s-const-t-defaultvalue-unsigned-index-0"></a>
##### T atOr(const C&amp; container, const std::string&amp; s, const T&amp; defaultValue, unsigned index = 0) 
###### *Param:* container 
###### *Param:* s 
###### *Param:* defaultValue 
###### *Param:* index 
###### *Return:*  
<a id="container-splitconst-stdstring-str-const-char-splitchar-39-39"></a>
##### Container split(const std::string&amp; str, const char splitChar = &#39; &#39;) 
###### *Param:* str 
###### *Param:* splitChar 
###### *Return:*  
<a id="stdstring-joinconst-it-begin-const-it-end-const-stdstring-joinchar"></a>
##### std::string join(const IT&amp; begin, const IT&amp; end, const std::string joinChar = &quot;&quot; ) 
###### *Param:* begin 
###### *Param:* end 
###### *Param:* joinChar 
###### *Return:*  
<a id="stdstring-joinconst-t-t-const-stdstring-joinchar"></a>
##### std::string join(const T&amp; t, const std::string joinChar = &quot;&quot; ) 
###### *Param:* t 
###### *Param:* joinChar 
###### *Return:*  
<a id="t-mergeconst-t-b1-const-t-b2"></a>
##### T merge(const T&amp; b1, const T&amp; b2) 
###### *Param:* b1 
###### *Param:* b2 
###### *Return:*  
<a id="t-tolowconst-t-str"></a>
##### T toLow(const T&amp; str) 
###### *Param:* str 
###### *Return:*  

---

---
##### Misc Utils 

---

---
##### File Utils 
<a id="stdstring-getlinkconst-stdstring-fname"></a>
#####  std::string getLink(const std::string&amp; fname) 
###### *Param:* fname 
###### *Return:*  
<a id="bool-isdirconst-stdstring-fname"></a>
#####  bool isDir(const std::string&amp; fname) 
###### *Param:* fname 
###### *Return:*  
<a id="stdstring-workingdir"></a>
#####  std::string workingDir() 
###### *Return:*  
<a id="stdstring-abspathconst-stdstring-rpath"></a>
#####  std::string absPath(const std::string&amp; rpath) 
###### *Param:* rpath 
###### *Return:*  
<a id="stdstring-pathpopconst-stdstring-filename"></a>
#####  std::string pathPop(const std::string&amp; filename) 
###### *Param:* filename 
###### *Return:*  
<a id="stdvectorstdtuplestdstring-bool-stdstring-directoryconst-stdstring-dirname"></a>
#####  std::vector&lt;std::tuple&lt;std::string, bool, std::string&gt;&gt; directory(const std::string&amp; dirname) 
###### *Param:* dirname 
###### *Return:*  
<a id="stdstring-tempname"></a>
#####  std::string tempName() 
###### *Return:*  
<a id="stdstring-systemenvconst-stdstring-env"></a>
#####  std::string systemEnv(const std::string&amp; env) 
###### *Param:* env 
###### *Return:*  
<a id="ssize_t-filesizeconst-stdstring-filename"></a>
#####  SSIZE_T fileSize(const std::string&amp; filename) 
###### *Param:* filename 
###### *Return:*  
<a id="bool-renameconst-stdstring-of-const-stdstring-nf"></a>
#####  bool rename(const std::string&amp; of, const std::string&amp; nf) 
###### *Param:* of 
###### *Param:* nf 
###### *Return:*  
<a id="void-removefileconst-stdstring-filename"></a>
#####  void removeFile(const std::string&amp; filename) 
###### *Param:* filename 
<a id="bool-fileexistsconst-stdstring-filename"></a>
#####  bool fileExists(const std::string&amp; filename) 
###### *Param:* filename 
###### *Return:*  
<a id="stdstring-writetotempconst-t-data"></a>
##### std::string writeToTemp(const T&amp; data) 
###### *Param:* data 
###### *Return:*  
<a id="stdvectort-slurpconst-stdstring-file-const-size_t-max-stdnumeric_limitssize_tmax"></a>
##### std::vector&lt;T&gt; slurp(const std::string&amp; file, const size_t max = std::numeric_limits&lt;size_t&gt;::max()) 
###### *Param:* file 
###### *Param:* max 
###### *Return:*  
<a id="stdstring-slurpconst-stdstring-file-const-size_t-max-stdnumeric_limitssize_tmax"></a>
#####  std::string slurp(const std::string&amp; file, const size_t max = std::numeric_limits&lt;size_t&gt;::max()) 
###### *Param:* file 
###### *Param:* max 
###### *Return:*  

---
###### Generated by MarkdownMaker, (c) Markus Mertama 2020 
