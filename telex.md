![wqe](https://avatars1.githubusercontent.com/u/7837709?s=400&amp;v=4)

Telex
=====
GUI Framework
-------------

telex.h contains core functionality, everything that is needed for basic application using Telex framework.


* [ namespace Telex ](#telex)
  * [  void setDebug() ](#-void-setdebug-)
  * [ class Element ](#element)
    * [ Element(Ui&amp; ui, const std::string&amp; id) ](#element-ui-amp-ui-const-std-string-amp-id-)
    * [ Element(Ui&amp; ui, const std::string&amp; id, const std::string&amp; htmlElement, const Element&amp; parent) ](#element-ui-amp-ui-const-std-string-amp-id-const-std-string-amp-htmlelement-const-element-amp-parent-)
    * [ const Ui&amp; ui() const ](#const-ui-amp-ui-const)
    * [ Ui&amp; ui() ](#ui-amp-ui-)
    * [ std::string id() const ](#std-string-id-const)
    * [ Element&amp; subscribe(const std::string&amp; name, std::function&amp;lt;void(const Event&amp; ev)&gt; handler, const std::vector&amp;lt;std::string&gt;&amp; properties = {}, const std::chrono::milliseconds&amp; = 0ms) ](#element-amp-subscribe-const-std-string-amp-name-std-function-amp-lt-void-const-event-amp-ev-gt-handler-const-std-vector-amp-lt-std-string-gt-amp-properties-const-std-chrono-milliseconds-amp-0ms-)
    * [ Element&amp; setHTML(const std::string&amp; htmlText) ](#element-amp-sethtml-const-std-string-amp-htmltext-)
    * [ Element&amp; setAttribute(const std::string&amp; attr, const std::string&amp; values) ](#element-amp-setattribute-const-std-string-amp-attr-const-std-string-amp-values-)
    * [ std::optional&amp;lt;Attributes&gt; attributes() const ](#std-optional-amp-lt-attributes-gt-attributes-const)
    * [ std::optional&amp;lt;Elements&gt; children() const ](#std-optional-amp-lt-elements-gt-children-const)
    * [ std::optional&amp;lt;Values&gt; values() const ](#std-optional-amp-lt-values-gt-values-const)
    * [ std::optional&amp;lt;std::string&gt; html() const ](#std-optional-amp-lt-std-string-gt-html-const)
    * [ void remove() ](#void-remove-)
    * [ std::optional&amp;lt;std::string&gt; type() const ](#std-optional-amp-lt-std-string-gt-type-const)
    * [ std::optional&amp;lt;Rect&gt; rect() const ](#std-optional-amp-lt-rect-gt-rect-const)
  * [ class Ui ](#ui)
    * [ explicit Ui(const std::string&amp; indexHtml, const std::string&amp; browser, const std::string&amp; extraParams = &quot;&quot;, unsigned short port = UseDefaultPort, const std::string&amp; root = UseDefaultRoot) ](#explicit-ui-const-std-string-amp-indexhtml-const-std-string-amp-browser-const-std-string-amp-extraparams-quot-quot-unsigned-short-port-usedefaultport-const-std-string-amp-root-usedefaultroot-)
    * [ explicit Ui(const std::string&amp; indexHtml, unsigned short port = UseDefaultPort, const std::string&amp; root = UseDefaultRoot) ](#explicit-ui-const-std-string-amp-indexhtml-unsigned-short-port-usedefaultport-const-std-string-amp-root-usedefaultroot-)
    * [ explicit Ui(const Filemap&amp; filemap, const std::string&amp; indexHtml, const std::string&amp; browser, const std::string&amp; extraParams = &quot;&quot;, unsigned short port = UseDefaultPort, const std::string&amp; root = UseDefaultRoot) ](#explicit-ui-const-filemap-amp-filemap-const-std-string-amp-indexhtml-const-std-string-amp-browser-const-std-string-amp-extraparams-quot-quot-unsigned-short-port-usedefaultport-const-std-string-amp-root-usedefaultroot-)
    * [ explicit Ui(const Filemap&amp; filemap, const std::string&amp; indexHtml, unsigned short port = UseDefaultPort, const std::string&amp; root = UseDefaultRoot) ](#explicit-ui-const-filemap-amp-filemap-const-std-string-amp-indexhtml-unsigned-short-port-usedefaultport-const-std-string-amp-root-usedefaultroot-)
    * [ void exit() ](#void-exit-)
    * [ void close() ](#void-close-)
    * [ Ui&amp; onUiExit(std::function&amp;lt;void ()&gt; onExitFunction = nullptr) ](#ui-amp-onuiexit-std-function-amp-lt-void-gt-onexitfunction-nullptr-)
    * [ Ui&amp; onReload(std::function&amp;lt;void ()&gt; onReleadFunction = nullptr) ](#ui-amp-onreload-std-function-amp-lt-void-gt-onreleadfunction-nullptr-)
    * [ Ui&amp; onOpen(std::function&amp;lt;void ()&gt; onOpenFunction = nullptr) ](#ui-amp-onopen-std-function-amp-lt-void-gt-onopenfunction-nullptr-)
    * [ Ui&amp; onError(std::function&amp;lt;void (const std::string&amp; element, const std::string&amp; info)&gt; onErrorFunction = nullptr) ](#ui-amp-onerror-std-function-amp-lt-void-const-std-string-amp-element-const-std-string-amp-info-gt-onerrorfunction-nullptr-)
    * [ void run() ](#void-run-)
    * [ void setLogging(bool logging) ](#void-setlogging-bool-logging-)
    * [ void eval(const std::string&amp; eval) ](#void-eval-const-std-string-amp-eval-)
    * [ void debug(const std::string&amp; msg) ](#void-debug-const-std-string-amp-msg-)
    * [ void alert(const std::string&amp; msg) ](#void-alert-const-std-string-amp-msg-)
    * [ void open(const std::string&amp; url, const std::string&amp; name = &quot;&quot;) ](#void-open-const-std-string-amp-url-const-std-string-amp-name-quot-quot-)
    * [ TimerId startTimer(const std::chrono::milliseconds&amp; ms, bool singleShot, const std::function&amp;lt;void (TimerId id)&gt;&amp; timerFunc) ](#timerid-starttimer-const-std-chrono-milliseconds-amp-ms-bool-singleshot-const-std-function-amp-lt-void-timerid-id-gt-amp-timerfunc-)
    * [ TimerId startTimer(const std::chrono::milliseconds&amp; ms, bool singleShot, const std::function&amp;lt;void ()&gt;&amp; timerFunc) ](#timerid-starttimer-const-std-chrono-milliseconds-amp-ms-bool-singleshot-const-std-function-amp-lt-void-gt-amp-timerfunc-)
    * [ bool stopTimer(TimerId) ](#bool-stoptimer-timerid-)
    * [ Element root() const ](#element-root-const)
    * [ std::string addressOf(const std::string&amp; filepath) const ](#std-string-addressof-const-std-string-amp-filepath-const)
    * [ std::optional&amp;lt;Element::Elements&gt; byClass(const std::string&amp; className) const ](#std-optional-amp-lt-element-elements-gt-byclass-const-std-string-amp-classname-const)
    * [ std::optional&amp;lt;Element::Elements&gt; byName(const std::string&amp; className) const ](#std-optional-amp-lt-element-elements-gt-byname-const-std-string-amp-classname-const)
    * [ std::optional&amp;lt;std::pair&amp;lt;std::chrono::microseconds, std::chrono::microseconds&gt;&gt; ping() const ](#std-optional-amp-lt-std-pair-amp-lt-std-chrono-microseconds-std-chrono-microseconds-gt-gt-ping-const)
    * [ std::optional&amp;lt;std::any&gt; extension(const std::string&amp; callId, const std::unordered_map&amp;lt;std::string, std::any&gt;&amp; parameters) ](#std-optional-amp-lt-std-any-gt-extension-const-std-string-amp-callid-const-std-unordered_map-amp-lt-std-string-std-any-gt-amp-parameters-)
    * [ std::optional&amp;lt;std::vector&amp;lt;uint8_t&gt;&gt; resource(const std::string&amp; url) const ](#std-optional-amp-lt-std-vector-amp-lt-uint8_t-gt-gt-resource-const-std-string-amp-url-const)
    * [ bool addFile(const std::string&amp; url, const std::string&amp; file) ](#bool-addfile-const-std-string-amp-url-const-std-string-amp-file-)
    * [ void beginBatch() ](#void-beginbatch-)
    * [ void endBatch() ](#void-endbatch-)


---
<a name=""></a>
#####
Telex contains three header files
* `telex.h`
* `telex_utils.h`
* `telex_graphics.h`

---

---
<a name="Telex"></a>
### Telex

Common namespace for Telex implementation.
<a name="#-void-setdebug-"></a>
#####  void setDebug()
Enable debug outputs

---

---
<a name="Element"></a>
#### Telex::Element

Element represents any UI element
<a name="#element-ui-amp-ui-const-std-string-amp-id-"></a>
##### Element(Ui&amp; ui, const std::string&amp; id)
<a name=""></a>
###### *Param:* ui
<a name=""></a>
###### *Param:* id

Creates instance that refers to existing element.
<a name="#element-ui-amp-ui-const-std-string-amp-id-const-std-string-amp-htmlelement-const-element-amp-parent-"></a>
##### Element(Ui&amp; ui, const std::string&amp; id, const std::string&amp; htmlElement, const Element&amp; parent)
<a name=""></a>
###### *Param:* ui
<a name=""></a>
###### *Param:* id
<a name=""></a>
###### *Param:* htmlElement
<a name=""></a>
###### *Param:* parent

Creates a new elements as given HTML type and parent.
<a name="#const-ui-amp-ui-const"></a>
##### const Ui&amp; ui() const
<a name=""></a>
###### *Return:* Ui

Return current Ui.
<a name="#ui-amp-ui-"></a>
##### Ui&amp; ui()
<a name=""></a>
###### *Return:* Ui

Return current Ui.
<a name="#std-string-id-const"></a>
##### std::string id() const
<a name=""></a>
###### *Return:* string

HTML identifer of this element
<a name="#element-amp-subscribe-const-std-string-amp-name-std-function-amp-lt-void-const-event-amp-ev-gt-handler-const-std-vector-amp-lt-std-string-gt-amp-properties-const-std-chrono-milliseconds-amp-0ms-"></a>
##### Element&amp; subscribe(const std::string&amp; name, std::function&amp;lt;void(const Event&amp; ev)&gt; handler, const std::vector&amp;lt;std::string&gt;&amp; properties = {}, const std::chrono::milliseconds&amp; = 0ms)
<a name=""></a>
###### *Param:* name
<a name=""></a>
###### *Param:* handler
<a name=""></a>
###### *Param:* throttle
<a name=""></a>
###### *Return:* Element

Set a function to listen ui event.
<a name="#element-amp-sethtml-const-std-string-amp-htmltext-"></a>
##### Element&amp; setHTML(const std::string&amp; htmlText)
<a name=""></a>
###### *Param:* name
<a name=""></a>
###### *Param:* handler
<a name=""></a>
###### *Return:* Element

Set HTML content for element.
<a name="#element-amp-setattribute-const-std-string-amp-attr-const-std-string-amp-values-"></a>
##### Element&amp; setAttribute(const std::string&amp; attr, const std::string&amp; values)
<a name=""></a>
###### *Param:* attr
<a name=""></a>
###### *Param:* values
<a name=""></a>
###### *Return:* Element

Set a given attribute a given name
<a name="#std-optional-amp-lt-attributes-gt-attributes-const"></a>
##### std::optional&amp;lt;Attributes&gt; attributes() const
<a name=""></a>
###### *Return:* optional Attributes

Return Attributes.
<a name="#std-optional-amp-lt-elements-gt-children-const"></a>
##### std::optional&amp;lt;Elements&gt; children() const
<a name=""></a>
###### *Return:* optional Elements

Return child elements (only direct children).
<a name="#std-optional-amp-lt-values-gt-values-const"></a>
##### std::optional&amp;lt;Values&gt; values() const
<a name=""></a>
###### *Return:* optional Values

Return values. (e.g. input values).
<a name="#std-optional-amp-lt-std-string-gt-html-const"></a>
##### std::optional&amp;lt;std::string&gt; html() const
<a name=""></a>
###### *Return:* optional string

Return html content of this element.
<a name="#void-remove-"></a>
##### void remove()

Remove this element from Ui.
<a name="#std-optional-amp-lt-std-string-gt-type-const"></a>
##### std::optional&amp;lt;std::string&gt; type() const
<a name=""></a>
###### *Return:* optiona string.

Return type as HTML tag in lower case, empty is not found.
<a name="#std-optional-amp-lt-rect-gt-rect-const"></a>
##### std::optional&amp;lt;Rect&gt; rect() const
<a name=""></a>
###### *Return:* optional Rect

Return bounding rect of element

---

---
<a name="Ui"></a>
#### Telex::Ui
<a name="#explicit-ui-const-std-string-amp-indexhtml-const-std-string-amp-browser-const-std-string-amp-extraparams-quot-quot-unsigned-short-port-usedefaultport-const-std-string-amp-root-usedefaultroot-"></a>
##### explicit Ui(const std::string&amp; indexHtml, const std::string&amp; browser, const std::string&amp; extraParams = &quot;&quot;, unsigned short port = UseDefaultPort, const std::string&amp; root = UseDefaultRoot)
<a name=""></a>
###### *Param:* indexHtml
<a name=""></a>
###### *Param:* browser
<a name=""></a>
###### *Param:* extraParams
<a name=""></a>
###### *Param:* port, has default
<a name=""></a>
###### *Param:* root, has default

Constructor
<a name="#explicit-ui-const-std-string-amp-indexhtml-unsigned-short-port-usedefaultport-const-std-string-amp-root-usedefaultroot-"></a>
##### explicit Ui(const std::string&amp; indexHtml, unsigned short port = UseDefaultPort, const std::string&amp; root = UseDefaultRoot)
<a name=""></a>
###### *Param:* indexHtml
<a name=""></a>
###### *Param:* port, has default
<a name=""></a>
###### *Param:* root, has default

Constructor
<a name="#explicit-ui-const-filemap-amp-filemap-const-std-string-amp-indexhtml-const-std-string-amp-browser-const-std-string-amp-extraparams-quot-quot-unsigned-short-port-usedefaultport-const-std-string-amp-root-usedefaultroot-"></a>
##### explicit Ui(const Filemap&amp; filemap, const std::string&amp; indexHtml, const std::string&amp; browser, const std::string&amp; extraParams = &quot;&quot;, unsigned short port = UseDefaultPort, const std::string&amp; root = UseDefaultRoot)
<a name=""></a>
###### *Param:* filemap
<a name=""></a>
###### *Param:* indexHtml
<a name=""></a>
###### *Param:* browser
<a name=""></a>
###### *Param:* extraParams, has defaul
<a name=""></a>
###### *Param:* port, has default
<a name=""></a>
###### *Param:* root, has default

Constructor
<a name="#explicit-ui-const-filemap-amp-filemap-const-std-string-amp-indexhtml-unsigned-short-port-usedefaultport-const-std-string-amp-root-usedefaultroot-"></a>
##### explicit Ui(const Filemap&amp; filemap, const std::string&amp; indexHtml, unsigned short port = UseDefaultPort, const std::string&amp; root = UseDefaultRoot)
<a name=""></a>
###### *Param:* filemap
<a name=""></a>
###### *Param:* indexHtml
<a name=""></a>
###### *Param:* port, has default
<a name=""></a>
###### *Param:* root, has default

Constructor
<a name="#void-exit-"></a>
##### void exit()

Exits the eventloop and make application to close.
<a name="#void-close-"></a>
##### void close()

Asks Client window to close (which then signals application to close)
<a name="#ui-amp-onuiexit-std-function-amp-lt-void-gt-onexitfunction-nullptr-"></a>
##### Ui&amp; onUiExit(std::function&amp;lt;void ()&gt; onExitFunction = nullptr)
<a name=""></a>
###### *Param:* onExitFunction
<a name=""></a>
###### *Return:* Ui

Callback just before exit.
<a name="#ui-amp-onreload-std-function-amp-lt-void-gt-onreleadfunction-nullptr-"></a>
##### Ui&amp; onReload(std::function&amp;lt;void ()&gt; onReleadFunction = nullptr)
<a name=""></a>
###### *Param:* onReleadFunction
<a name=""></a>
###### *Return:* Ui

Callback when browser window reload occurs.
<a name="#ui-amp-onopen-std-function-amp-lt-void-gt-onopenfunction-nullptr-"></a>
##### Ui&amp; onOpen(std::function&amp;lt;void ()&gt; onOpenFunction = nullptr)
<a name=""></a>
###### *Param:* onOpenFunction
<a name=""></a>
###### *Return:* Ui

Callback when browser UI is running.
<a name="#ui-amp-onerror-std-function-amp-lt-void-const-std-string-amp-element-const-std-string-amp-info-gt-onerrorfunction-nullptr-"></a>
##### Ui&amp; onError(std::function&amp;lt;void (const std::string&amp; element, const std::string&amp; info)&gt; onErrorFunction = nullptr)
<a name=""></a>
###### *Param:* onErrorFunction
<a name=""></a>
###### *Return:* Ui

Browser reports an issue
<a name="#void-run-"></a>
##### void run()

Starts eventloop
<a name="#void-setlogging-bool-logging-"></a>
##### void setLogging(bool logging)
<a name=""></a>
###### *Param:* logging

Enforces Browser being verbose when serving Telex.
<a name="#void-eval-const-std-string-amp-eval-"></a>
##### void eval(const std::string&amp; eval)
<a name=""></a>
###### *Param:* eval

Execute code on browser (calls JS eval)
<a name="#void-debug-const-std-string-amp-msg-"></a>
##### void debug(const std::string&amp; msg)
<a name=""></a>
###### *Param:* msg

Echoes a message
<a name="#void-alert-const-std-string-amp-msg-"></a>
##### void alert(const std::string&amp; msg)
<a name=""></a>
###### *Param:* msg

Shown a browser&amp;#39;s alert dialogue
<a name="#void-open-const-std-string-amp-url-const-std-string-amp-name-quot-quot-"></a>
##### void open(const std::string&amp; url, const std::string&amp; name = &quot;&quot;)
<a name=""></a>
###### *Param:* url
<a name=""></a>
###### *Param:* name

Opens an extrenal URL on browser tab
<a name="#timerid-starttimer-const-std-chrono-milliseconds-amp-ms-bool-singleshot-const-std-function-amp-lt-void-timerid-id-gt-amp-timerfunc-"></a>
##### TimerId startTimer(const std::chrono::milliseconds&amp; ms, bool singleShot, const std::function&amp;lt;void (TimerId id)&gt;&amp; timerFunc)
<a name=""></a>
###### *Param:* ms
<a name=""></a>
###### *Param:* singleShot
<a name=""></a>
###### *Param:* timerFunc
<a name=""></a>
###### *Return:* TimerId

Starts a timer that is called after given amount of milliseconds.
<a name="#timerid-starttimer-const-std-chrono-milliseconds-amp-ms-bool-singleshot-const-std-function-amp-lt-void-gt-amp-timerfunc-"></a>
##### TimerId startTimer(const std::chrono::milliseconds&amp; ms, bool singleShot, const std::function&amp;lt;void ()&gt;&amp; timerFunc)
<a name=""></a>
###### *Param:* ms
<a name=""></a>
###### *Param:* singleShot
<a name=""></a>
###### *Param:* timerFunc
<a name=""></a>
###### *Return:* TimerId

Starts a timer that is called after given amount of milliseconds.
<a name="#bool-stoptimer-timerid-"></a>
##### bool stopTimer(TimerId)
<a name=""></a>
###### *Return:* Boolean

Stop the timer.
<a name="#element-root-const"></a>
##### Element root() const
<a name=""></a>
###### *Return:* Element

Pseudo element that represents root of the element structure
<a name="#std-string-addressof-const-std-string-amp-filepath-const"></a>
##### std::string addressOf(const std::string&amp; filepath) const
<a name=""></a>
###### *Param:* filepath
<a name=""></a>
###### *Return:* string

Translates given path to address that Telex can read when provided as a link.
<a name="#std-optional-amp-lt-element-elements-gt-byclass-const-std-string-amp-classname-const"></a>
##### std::optional&amp;lt;Element::Elements&gt; byClass(const std::string&amp; className) const
<a name=""></a>
###### *Param:* className
<a name=""></a>
###### *Return:* optional list of Elements

Returns all elements match to given class
<a name="#std-optional-amp-lt-element-elements-gt-byname-const-std-string-amp-classname-const"></a>
##### std::optional&amp;lt;Element::Elements&gt; byName(const std::string&amp; className) const
<a name=""></a>
###### *Param:* className
<a name=""></a>
###### *Return:* optional list of Elements.

Returns all elements match to given name
<a name="#std-optional-amp-lt-std-pair-amp-lt-std-chrono-microseconds-std-chrono-microseconds-gt-gt-ping-const"></a>
##### std::optional&amp;lt;std::pair&amp;lt;std::chrono::microseconds, std::chrono::microseconds&gt;&gt; ping() const
<a name=""></a>
###### *Return:* optional pair of times.

Just a ping.
<a name="#std-optional-amp-lt-std-any-gt-extension-const-std-string-amp-callid-const-std-unordered_map-amp-lt-std-string-std-any-gt-amp-parameters-"></a>
##### std::optional&amp;lt;std::any&gt; extension(const std::string&amp; callId, const std::unordered_map&amp;lt;std::string, std::any&gt;&amp; parameters)
<a name=""></a>
###### *Param:* callId
<a name=""></a>
###### *Param:* parameters
<a name=""></a>
###### *Return:* optional any

Low level access to extension services that browser may implement. The return parameter and return value are JSON kind
of structures or types and depends on given callId.
Note if return value contain a string it is very straighforward

for example
```
const auto out = ui.extension("openFile", {{"caption", "hexview - open"}});
const std::string filename = std::any_cast<std::string>(*out);
```
but if is an array of string values must be converted accordint to structure
```
const auto out = ui.extension("openFile", {{"caption", "hexview - open"}});
const auto anyvec = std::any_cast<std::vector<std::any>(*out);
std::vector<std::string> vec;
std::transform(anyvec.begin(), anyvec.end, std::back_inserter(vec), [](const auto& a){return std::any_cast<std::string>(a)});
```
<a name="#std-optional-amp-lt-std-vector-amp-lt-uint8_t-gt-gt-resource-const-std-string-amp-url-const"></a>
##### std::optional&amp;lt;std::vector&amp;lt;uint8_t&gt;&gt; resource(const std::string&amp; url) const
<a name=""></a>
###### *Param:* url
<a name=""></a>
###### *Return:* optional byte vector

Get data stored as a resource
<a name="#bool-addfile-const-std-string-amp-url-const-std-string-amp-file-"></a>
##### bool addFile(const std::string&amp; url, const std::string&amp; file)
<a name=""></a>
###### *Param:* url
<a name=""></a>
###### *Param:* file
<a name=""></a>
###### *Return:* boolean

Adds a file as a resources
<a name="#void-beginbatch-"></a>
##### void beginBatch()

Starts buffering non-DataPtr message locally
<a name="#void-endbatch-"></a>
##### void endBatch()

Sends locally buffered message to UI

---
###### Generated by MarkdownMaker, (c) Markus Mertama 2020
