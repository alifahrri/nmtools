

// The Module object: Our interface to the outside world. We import
// and export values on it. There are various ways Module can be used:
// 1. Not defined. We create it here
// 2. A function parameter, function(Module) { ..generated code.. }
// 3. pre-run appended it, var Module = {}; ..generated code..
// 4. External script tag defines var Module.
// We need to check if Module already exists (e.g. case 3 above).
// Substitution will be replaced with actual code on later stage of the build,
// this way Closure Compiler will not mangle it (e.g. case 4. above).
// Note that if you want to run closure, and also to use Module
// after the generated code, you will need to define   var Module = {};
// before the code. Then that object will be used in the code, and you
// can continue to use Module afterwards as well.
var Module = typeof Module !== 'undefined' ? Module : {};

// --pre-jses are emitted after the Module integration code, so that they can
// refer to Module (if they choose; they can also define Module)
// {{PRE_JSES}}

// Sometimes an existing Module object exists with properties
// meant to overwrite the default module functionality. Here
// we collect those properties and reapply _after_ we configure
// the current environment's defaults to avoid having to be so
// defensive during initialization.
var moduleOverrides = {};
var key;
for (key in Module) {
  if (Module.hasOwnProperty(key)) {
    moduleOverrides[key] = Module[key];
  }
}

var arguments_ = [];
var thisProgram = './this.program';
var quit_ = function(status, toThrow) {
  throw toThrow;
};

// Determine the runtime environment we are in. You can customize this by
// setting the ENVIRONMENT setting at compile time (see settings.js).

// Attempt to auto-detect the environment
var ENVIRONMENT_IS_WEB = typeof window === 'object';
var ENVIRONMENT_IS_WORKER = typeof importScripts === 'function';
// N.b. Electron.js environment is simultaneously a NODE-environment, but
// also a web environment.
var ENVIRONMENT_IS_NODE = typeof process === 'object' && typeof process.versions === 'object' && typeof process.versions.node === 'string';
var ENVIRONMENT_IS_SHELL = !ENVIRONMENT_IS_WEB && !ENVIRONMENT_IS_NODE && !ENVIRONMENT_IS_WORKER;

if (Module['ENVIRONMENT']) {
  throw new Error('Module.ENVIRONMENT has been deprecated. To force the environment, use the ENVIRONMENT compile-time option (for example, -s ENVIRONMENT=web or -s ENVIRONMENT=node)');
}

// `/` should be present at the end if `scriptDirectory` is not empty
var scriptDirectory = '';
function locateFile(path) {
  if (Module['locateFile']) {
    return Module['locateFile'](path, scriptDirectory);
  }
  return scriptDirectory + path;
}

// Hooks that are implemented differently in different runtime environments.
var read_,
    readAsync,
    readBinary,
    setWindowTitle;

// Normally we don't log exceptions but instead let them bubble out the top
// level where the embedding environment (e.g. the browser) can handle
// them.
// However under v8 and node we sometimes exit the process direcly in which case
// its up to use us to log the exception before exiting.
// If we fix https://github.com/emscripten-core/emscripten/issues/15080
// this may no longer be needed under node.
function logExceptionOnExit(e) {
  if (e instanceof ExitStatus) return;
  var toLog = e;
  if (e && typeof e === 'object' && e.stack) {
    toLog = [e, e.stack];
  }
  err('exiting due to exception: ' + toLog);
}

var nodeFS;
var nodePath;

if (ENVIRONMENT_IS_NODE) {
  if (!(typeof process === 'object' && typeof require === 'function')) throw new Error('not compiled for this environment (did you build to HTML and try to run it not on the web, or set ENVIRONMENT to something - like node - and run it someplace else - like on the web?)');
  if (ENVIRONMENT_IS_WORKER) {
    scriptDirectory = require('path').dirname(scriptDirectory) + '/';
  } else {
    scriptDirectory = __dirname + '/';
  }

// include: node_shell_read.js


read_ = function shell_read(filename, binary) {
  var ret = tryParseAsDataURI(filename);
  if (ret) {
    return binary ? ret : ret.toString();
  }
  if (!nodeFS) nodeFS = require('fs');
  if (!nodePath) nodePath = require('path');
  filename = nodePath['normalize'](filename);
  return nodeFS['readFileSync'](filename, binary ? null : 'utf8');
};

readBinary = function readBinary(filename) {
  var ret = read_(filename, true);
  if (!ret.buffer) {
    ret = new Uint8Array(ret);
  }
  assert(ret.buffer);
  return ret;
};

readAsync = function readAsync(filename, onload, onerror) {
  var ret = tryParseAsDataURI(filename);
  if (ret) {
    onload(ret);
  }
  if (!nodeFS) nodeFS = require('fs');
  if (!nodePath) nodePath = require('path');
  filename = nodePath['normalize'](filename);
  nodeFS['readFile'](filename, function(err, data) {
    if (err) onerror(err);
    else onload(data.buffer);
  });
};

// end include: node_shell_read.js
  if (process['argv'].length > 1) {
    thisProgram = process['argv'][1].replace(/\\/g, '/');
  }

  arguments_ = process['argv'].slice(2);

  if (typeof module !== 'undefined') {
    module['exports'] = Module;
  }

  process['on']('uncaughtException', function(ex) {
    // suppress ExitStatus exceptions from showing an error
    if (!(ex instanceof ExitStatus)) {
      throw ex;
    }
  });

  // Without this older versions of node (< v15) will log unhandled rejections
  // but return 0, which is not normally the desired behaviour.  This is
  // not be needed with node v15 and about because it is now the default
  // behaviour:
  // See https://nodejs.org/api/cli.html#cli_unhandled_rejections_mode
  process['on']('unhandledRejection', function(reason) { throw reason; });

  quit_ = function(status, toThrow) {
    if (keepRuntimeAlive()) {
      process['exitCode'] = status;
      throw toThrow;
    }
    logExceptionOnExit(toThrow);
    process['exit'](status);
  };

  Module['inspect'] = function () { return '[Emscripten Module object]'; };

} else
if (ENVIRONMENT_IS_SHELL) {

  if ((typeof process === 'object' && typeof require === 'function') || typeof window === 'object' || typeof importScripts === 'function') throw new Error('not compiled for this environment (did you build to HTML and try to run it not on the web, or set ENVIRONMENT to something - like node - and run it someplace else - like on the web?)');

  if (typeof read != 'undefined') {
    read_ = function shell_read(f) {
      var data = tryParseAsDataURI(f);
      if (data) {
        return intArrayToString(data);
      }
      return read(f);
    };
  }

  readBinary = function readBinary(f) {
    var data;
    data = tryParseAsDataURI(f);
    if (data) {
      return data;
    }
    if (typeof readbuffer === 'function') {
      return new Uint8Array(readbuffer(f));
    }
    data = read(f, 'binary');
    assert(typeof data === 'object');
    return data;
  };

  readAsync = function readAsync(f, onload, onerror) {
    setTimeout(function() { onload(readBinary(f)); }, 0);
  };

  if (typeof scriptArgs != 'undefined') {
    arguments_ = scriptArgs;
  } else if (typeof arguments != 'undefined') {
    arguments_ = arguments;
  }

  if (typeof quit === 'function') {
    quit_ = function(status, toThrow) {
      logExceptionOnExit(toThrow);
      quit(status);
    };
  }

  if (typeof print !== 'undefined') {
    // Prefer to use print/printErr where they exist, as they usually work better.
    if (typeof console === 'undefined') console = /** @type{!Console} */({});
    console.log = /** @type{!function(this:Console, ...*): undefined} */ (print);
    console.warn = console.error = /** @type{!function(this:Console, ...*): undefined} */ (typeof printErr !== 'undefined' ? printErr : print);
  }

} else

// Note that this includes Node.js workers when relevant (pthreads is enabled).
// Node.js workers are detected as a combination of ENVIRONMENT_IS_WORKER and
// ENVIRONMENT_IS_NODE.
if (ENVIRONMENT_IS_WEB || ENVIRONMENT_IS_WORKER) {
  if (ENVIRONMENT_IS_WORKER) { // Check worker, not web, since window could be polyfilled
    scriptDirectory = self.location.href;
  } else if (typeof document !== 'undefined' && document.currentScript) { // web
    scriptDirectory = document.currentScript.src;
  }
  // blob urls look like blob:http://site.com/etc/etc and we cannot infer anything from them.
  // otherwise, slice off the final part of the url to find the script directory.
  // if scriptDirectory does not contain a slash, lastIndexOf will return -1,
  // and scriptDirectory will correctly be replaced with an empty string.
  // If scriptDirectory contains a query (starting with ?) or a fragment (starting with #),
  // they are removed because they could contain a slash.
  if (scriptDirectory.indexOf('blob:') !== 0) {
    scriptDirectory = scriptDirectory.substr(0, scriptDirectory.replace(/[?#].*/, "").lastIndexOf('/')+1);
  } else {
    scriptDirectory = '';
  }

  if (!(typeof window === 'object' || typeof importScripts === 'function')) throw new Error('not compiled for this environment (did you build to HTML and try to run it not on the web, or set ENVIRONMENT to something - like node - and run it someplace else - like on the web?)');

  // Differentiate the Web Worker from the Node Worker case, as reading must
  // be done differently.
  {

// include: web_or_worker_shell_read.js


  read_ = function(url) {
    try {
      var xhr = new XMLHttpRequest();
      xhr.open('GET', url, false);
      xhr.send(null);
      return xhr.responseText;
    } catch (err) {
      var data = tryParseAsDataURI(url);
      if (data) {
        return intArrayToString(data);
      }
      throw err;
    }
  };

  if (ENVIRONMENT_IS_WORKER) {
    readBinary = function(url) {
      try {
        var xhr = new XMLHttpRequest();
        xhr.open('GET', url, false);
        xhr.responseType = 'arraybuffer';
        xhr.send(null);
        return new Uint8Array(/** @type{!ArrayBuffer} */(xhr.response));
      } catch (err) {
        var data = tryParseAsDataURI(url);
        if (data) {
          return data;
        }
        throw err;
      }
    };
  }

  readAsync = function(url, onload, onerror) {
    var xhr = new XMLHttpRequest();
    xhr.open('GET', url, true);
    xhr.responseType = 'arraybuffer';
    xhr.onload = function() {
      if (xhr.status == 200 || (xhr.status == 0 && xhr.response)) { // file URLs can return 0
        onload(xhr.response);
        return;
      }
      var data = tryParseAsDataURI(url);
      if (data) {
        onload(data.buffer);
        return;
      }
      onerror();
    };
    xhr.onerror = onerror;
    xhr.send(null);
  };

// end include: web_or_worker_shell_read.js
  }

  setWindowTitle = function(title) { document.title = title };
} else
{
  throw new Error('environment detection error');
}

// Set up the out() and err() hooks, which are how we can print to stdout or
// stderr, respectively.
var out = Module['print'] || console.log.bind(console);
var err = Module['printErr'] || console.warn.bind(console);

// Merge back in the overrides
for (key in moduleOverrides) {
  if (moduleOverrides.hasOwnProperty(key)) {
    Module[key] = moduleOverrides[key];
  }
}
// Free the object hierarchy contained in the overrides, this lets the GC
// reclaim data used e.g. in memoryInitializerRequest, which is a large typed array.
moduleOverrides = null;

// Emit code to handle expected values on the Module object. This applies Module.x
// to the proper local x. This has two benefits: first, we only emit it if it is
// expected to arrive, and second, by using a local everywhere else that can be
// minified.

if (Module['arguments']) arguments_ = Module['arguments'];
if (!Object.getOwnPropertyDescriptor(Module, 'arguments')) {
  Object.defineProperty(Module, 'arguments', {
    configurable: true,
    get: function() {
      abort('Module.arguments has been replaced with plain arguments_ (the initial value can be provided on Module, but after startup the value is only looked for on a local variable of that name)')
    }
  });
}

if (Module['thisProgram']) thisProgram = Module['thisProgram'];
if (!Object.getOwnPropertyDescriptor(Module, 'thisProgram')) {
  Object.defineProperty(Module, 'thisProgram', {
    configurable: true,
    get: function() {
      abort('Module.thisProgram has been replaced with plain thisProgram (the initial value can be provided on Module, but after startup the value is only looked for on a local variable of that name)')
    }
  });
}

if (Module['quit']) quit_ = Module['quit'];
if (!Object.getOwnPropertyDescriptor(Module, 'quit')) {
  Object.defineProperty(Module, 'quit', {
    configurable: true,
    get: function() {
      abort('Module.quit has been replaced with plain quit_ (the initial value can be provided on Module, but after startup the value is only looked for on a local variable of that name)')
    }
  });
}

// perform assertions in shell.js after we set up out() and err(), as otherwise if an assertion fails it cannot print the message
// Assertions on removed incoming Module JS APIs.
assert(typeof Module['memoryInitializerPrefixURL'] === 'undefined', 'Module.memoryInitializerPrefixURL option was removed, use Module.locateFile instead');
assert(typeof Module['pthreadMainPrefixURL'] === 'undefined', 'Module.pthreadMainPrefixURL option was removed, use Module.locateFile instead');
assert(typeof Module['cdInitializerPrefixURL'] === 'undefined', 'Module.cdInitializerPrefixURL option was removed, use Module.locateFile instead');
assert(typeof Module['filePackagePrefixURL'] === 'undefined', 'Module.filePackagePrefixURL option was removed, use Module.locateFile instead');
assert(typeof Module['read'] === 'undefined', 'Module.read option was removed (modify read_ in JS)');
assert(typeof Module['readAsync'] === 'undefined', 'Module.readAsync option was removed (modify readAsync in JS)');
assert(typeof Module['readBinary'] === 'undefined', 'Module.readBinary option was removed (modify readBinary in JS)');
assert(typeof Module['setWindowTitle'] === 'undefined', 'Module.setWindowTitle option was removed (modify setWindowTitle in JS)');
assert(typeof Module['TOTAL_MEMORY'] === 'undefined', 'Module.TOTAL_MEMORY has been renamed Module.INITIAL_MEMORY');

if (!Object.getOwnPropertyDescriptor(Module, 'read')) {
  Object.defineProperty(Module, 'read', {
    configurable: true,
    get: function() {
      abort('Module.read has been replaced with plain read_ (the initial value can be provided on Module, but after startup the value is only looked for on a local variable of that name)')
    }
  });
}

if (!Object.getOwnPropertyDescriptor(Module, 'readAsync')) {
  Object.defineProperty(Module, 'readAsync', {
    configurable: true,
    get: function() {
      abort('Module.readAsync has been replaced with plain readAsync (the initial value can be provided on Module, but after startup the value is only looked for on a local variable of that name)')
    }
  });
}

if (!Object.getOwnPropertyDescriptor(Module, 'readBinary')) {
  Object.defineProperty(Module, 'readBinary', {
    configurable: true,
    get: function() {
      abort('Module.readBinary has been replaced with plain readBinary (the initial value can be provided on Module, but after startup the value is only looked for on a local variable of that name)')
    }
  });
}

if (!Object.getOwnPropertyDescriptor(Module, 'setWindowTitle')) {
  Object.defineProperty(Module, 'setWindowTitle', {
    configurable: true,
    get: function() {
      abort('Module.setWindowTitle has been replaced with plain setWindowTitle (the initial value can be provided on Module, but after startup the value is only looked for on a local variable of that name)')
    }
  });
}
var IDBFS = 'IDBFS is no longer included by default; build with -lidbfs.js';
var PROXYFS = 'PROXYFS is no longer included by default; build with -lproxyfs.js';
var WORKERFS = 'WORKERFS is no longer included by default; build with -lworkerfs.js';
var NODEFS = 'NODEFS is no longer included by default; build with -lnodefs.js';
function alignMemory() { abort('`alignMemory` is now a library function and not included by default; add it to your library.js __deps or to DEFAULT_LIBRARY_FUNCS_TO_INCLUDE on the command line'); }

assert(!ENVIRONMENT_IS_SHELL, "shell environment detected but not enabled at build time.  Add 'shell' to `-s ENVIRONMENT` to enable.");




var STACK_ALIGN = 16;

function getNativeTypeSize(type) {
  switch (type) {
    case 'i1': case 'i8': return 1;
    case 'i16': return 2;
    case 'i32': return 4;
    case 'i64': return 8;
    case 'float': return 4;
    case 'double': return 8;
    default: {
      if (type[type.length-1] === '*') {
        return 4; // A pointer
      } else if (type[0] === 'i') {
        var bits = Number(type.substr(1));
        assert(bits % 8 === 0, 'getNativeTypeSize invalid bits ' + bits + ', type ' + type);
        return bits / 8;
      } else {
        return 0;
      }
    }
  }
}

function warnOnce(text) {
  if (!warnOnce.shown) warnOnce.shown = {};
  if (!warnOnce.shown[text]) {
    warnOnce.shown[text] = 1;
    err(text);
  }
}

// include: runtime_functions.js


// Wraps a JS function as a wasm function with a given signature.
function convertJsFunctionToWasm(func, sig) {

  // If the type reflection proposal is available, use the new
  // "WebAssembly.Function" constructor.
  // Otherwise, construct a minimal wasm module importing the JS function and
  // re-exporting it.
  if (typeof WebAssembly.Function === "function") {
    var typeNames = {
      'i': 'i32',
      'j': 'i64',
      'f': 'f32',
      'd': 'f64'
    };
    var type = {
      parameters: [],
      results: sig[0] == 'v' ? [] : [typeNames[sig[0]]]
    };
    for (var i = 1; i < sig.length; ++i) {
      type.parameters.push(typeNames[sig[i]]);
    }
    return new WebAssembly.Function(type, func);
  }

  // The module is static, with the exception of the type section, which is
  // generated based on the signature passed in.
  var typeSection = [
    0x01, // id: section,
    0x00, // length: 0 (placeholder)
    0x01, // count: 1
    0x60, // form: func
  ];
  var sigRet = sig.slice(0, 1);
  var sigParam = sig.slice(1);
  var typeCodes = {
    'i': 0x7f, // i32
    'j': 0x7e, // i64
    'f': 0x7d, // f32
    'd': 0x7c, // f64
  };

  // Parameters, length + signatures
  typeSection.push(sigParam.length);
  for (var i = 0; i < sigParam.length; ++i) {
    typeSection.push(typeCodes[sigParam[i]]);
  }

  // Return values, length + signatures
  // With no multi-return in MVP, either 0 (void) or 1 (anything else)
  if (sigRet == 'v') {
    typeSection.push(0x00);
  } else {
    typeSection = typeSection.concat([0x01, typeCodes[sigRet]]);
  }

  // Write the overall length of the type section back into the section header
  // (excepting the 2 bytes for the section id and length)
  typeSection[1] = typeSection.length - 2;

  // Rest of the module is static
  var bytes = new Uint8Array([
    0x00, 0x61, 0x73, 0x6d, // magic ("\0asm")
    0x01, 0x00, 0x00, 0x00, // version: 1
  ].concat(typeSection, [
    0x02, 0x07, // import section
      // (import "e" "f" (func 0 (type 0)))
      0x01, 0x01, 0x65, 0x01, 0x66, 0x00, 0x00,
    0x07, 0x05, // export section
      // (export "f" (func 0 (type 0)))
      0x01, 0x01, 0x66, 0x00, 0x00,
  ]));

   // We can compile this wasm module synchronously because it is very small.
  // This accepts an import (at "e.f"), that it reroutes to an export (at "f")
  var module = new WebAssembly.Module(bytes);
  var instance = new WebAssembly.Instance(module, {
    'e': {
      'f': func
    }
  });
  var wrappedFunc = instance.exports['f'];
  return wrappedFunc;
}

var freeTableIndexes = [];

// Weak map of functions in the table to their indexes, created on first use.
var functionsInTableMap;

function getEmptyTableSlot() {
  // Reuse a free index if there is one, otherwise grow.
  if (freeTableIndexes.length) {
    return freeTableIndexes.pop();
  }
  // Grow the table
  try {
    wasmTable.grow(1);
  } catch (err) {
    if (!(err instanceof RangeError)) {
      throw err;
    }
    throw 'Unable to grow wasm table. Set ALLOW_TABLE_GROWTH.';
  }
  return wasmTable.length - 1;
}

// Add a wasm function to the table.
function addFunctionWasm(func, sig) {
  // Check if the function is already in the table, to ensure each function
  // gets a unique index. First, create the map if this is the first use.
  if (!functionsInTableMap) {
    functionsInTableMap = new WeakMap();
    for (var i = 0; i < wasmTable.length; i++) {
      var item = wasmTable.get(i);
      // Ignore null values.
      if (item) {
        functionsInTableMap.set(item, i);
      }
    }
  }
  if (functionsInTableMap.has(func)) {
    return functionsInTableMap.get(func);
  }

  // It's not in the table, add it now.

  var ret = getEmptyTableSlot();

  // Set the new value.
  try {
    // Attempting to call this with JS function will cause of table.set() to fail
    wasmTable.set(ret, func);
  } catch (err) {
    if (!(err instanceof TypeError)) {
      throw err;
    }
    assert(typeof sig !== 'undefined', 'Missing signature argument to addFunction: ' + func);
    var wrapped = convertJsFunctionToWasm(func, sig);
    wasmTable.set(ret, wrapped);
  }

  functionsInTableMap.set(func, ret);

  return ret;
}

function removeFunction(index) {
  functionsInTableMap.delete(wasmTable.get(index));
  freeTableIndexes.push(index);
}

// 'sig' parameter is required for the llvm backend but only when func is not
// already a WebAssembly function.
function addFunction(func, sig) {
  assert(typeof func !== 'undefined');

  return addFunctionWasm(func, sig);
}

// end include: runtime_functions.js
// include: runtime_debug.js


// end include: runtime_debug.js
var tempRet0 = 0;

var setTempRet0 = function(value) {
  tempRet0 = value;
};

var getTempRet0 = function() {
  return tempRet0;
};



// === Preamble library stuff ===

// Documentation for the public APIs defined in this file must be updated in:
//    site/source/docs/api_reference/preamble.js.rst
// A prebuilt local version of the documentation is available at:
//    site/build/text/docs/api_reference/preamble.js.txt
// You can also build docs locally as HTML or other formats in site/
// An online HTML version (which may be of a different version of Emscripten)
//    is up at http://kripken.github.io/emscripten-site/docs/api_reference/preamble.js.html

var wasmBinary;
if (Module['wasmBinary']) wasmBinary = Module['wasmBinary'];
if (!Object.getOwnPropertyDescriptor(Module, 'wasmBinary')) {
  Object.defineProperty(Module, 'wasmBinary', {
    configurable: true,
    get: function() {
      abort('Module.wasmBinary has been replaced with plain wasmBinary (the initial value can be provided on Module, but after startup the value is only looked for on a local variable of that name)')
    }
  });
}
var noExitRuntime = Module['noExitRuntime'] || true;
if (!Object.getOwnPropertyDescriptor(Module, 'noExitRuntime')) {
  Object.defineProperty(Module, 'noExitRuntime', {
    configurable: true,
    get: function() {
      abort('Module.noExitRuntime has been replaced with plain noExitRuntime (the initial value can be provided on Module, but after startup the value is only looked for on a local variable of that name)')
    }
  });
}

if (typeof WebAssembly !== 'object') {
  abort('no native wasm support detected');
}

// include: runtime_safe_heap.js


// In MINIMAL_RUNTIME, setValue() and getValue() are only available when building with safe heap enabled, for heap safety checking.
// In traditional runtime, setValue() and getValue() are always available (although their use is highly discouraged due to perf penalties)

/** @param {number} ptr
    @param {number} value
    @param {string} type
    @param {number|boolean=} noSafe */
function setValue(ptr, value, type, noSafe) {
  type = type || 'i8';
  if (type.charAt(type.length-1) === '*') type = 'i32'; // pointers are 32-bit
    switch (type) {
      case 'i1': HEAP8[((ptr)>>0)] = value; break;
      case 'i8': HEAP8[((ptr)>>0)] = value; break;
      case 'i16': HEAP16[((ptr)>>1)] = value; break;
      case 'i32': HEAP32[((ptr)>>2)] = value; break;
      case 'i64': (tempI64 = [value>>>0,(tempDouble=value,(+(Math.abs(tempDouble))) >= 1.0 ? (tempDouble > 0.0 ? ((Math.min((+(Math.floor((tempDouble)/4294967296.0))), 4294967295.0))|0)>>>0 : (~~((+(Math.ceil((tempDouble - +(((~~(tempDouble)))>>>0))/4294967296.0)))))>>>0) : 0)],HEAP32[((ptr)>>2)] = tempI64[0],HEAP32[(((ptr)+(4))>>2)] = tempI64[1]); break;
      case 'float': HEAPF32[((ptr)>>2)] = value; break;
      case 'double': HEAPF64[((ptr)>>3)] = value; break;
      default: abort('invalid type for setValue: ' + type);
    }
}

/** @param {number} ptr
    @param {string} type
    @param {number|boolean=} noSafe */
function getValue(ptr, type, noSafe) {
  type = type || 'i8';
  if (type.charAt(type.length-1) === '*') type = 'i32'; // pointers are 32-bit
    switch (type) {
      case 'i1': return HEAP8[((ptr)>>0)];
      case 'i8': return HEAP8[((ptr)>>0)];
      case 'i16': return HEAP16[((ptr)>>1)];
      case 'i32': return HEAP32[((ptr)>>2)];
      case 'i64': return HEAP32[((ptr)>>2)];
      case 'float': return HEAPF32[((ptr)>>2)];
      case 'double': return HEAPF64[((ptr)>>3)];
      default: abort('invalid type for getValue: ' + type);
    }
  return null;
}

// end include: runtime_safe_heap.js
// Wasm globals

var wasmMemory;

//========================================
// Runtime essentials
//========================================

// whether we are quitting the application. no code should run after this.
// set in exit() and abort()
var ABORT = false;

// set by exit() and abort().  Passed to 'onExit' handler.
// NOTE: This is also used as the process return code code in shell environments
// but only when noExitRuntime is false.
var EXITSTATUS;

/** @type {function(*, string=)} */
function assert(condition, text) {
  if (!condition) {
    abort('Assertion failed: ' + text);
  }
}

// Returns the C function with a specified identifier (for C++, you need to do manual name mangling)
function getCFunc(ident) {
  var func = Module['_' + ident]; // closure exported function
  assert(func, 'Cannot call unknown function ' + ident + ', make sure it is exported');
  return func;
}

// C calling interface.
/** @param {string|null=} returnType
    @param {Array=} argTypes
    @param {Arguments|Array=} args
    @param {Object=} opts */
function ccall(ident, returnType, argTypes, args, opts) {
  // For fast lookup of conversion functions
  var toC = {
    'string': function(str) {
      var ret = 0;
      if (str !== null && str !== undefined && str !== 0) { // null string
        // at most 4 bytes per UTF-8 code point, +1 for the trailing '\0'
        var len = (str.length << 2) + 1;
        ret = stackAlloc(len);
        stringToUTF8(str, ret, len);
      }
      return ret;
    },
    'array': function(arr) {
      var ret = stackAlloc(arr.length);
      writeArrayToMemory(arr, ret);
      return ret;
    }
  };

  function convertReturnValue(ret) {
    if (returnType === 'string') return UTF8ToString(ret);
    if (returnType === 'boolean') return Boolean(ret);
    return ret;
  }

  var func = getCFunc(ident);
  var cArgs = [];
  var stack = 0;
  assert(returnType !== 'array', 'Return type should not be "array".');
  if (args) {
    for (var i = 0; i < args.length; i++) {
      var converter = toC[argTypes[i]];
      if (converter) {
        if (stack === 0) stack = stackSave();
        cArgs[i] = converter(args[i]);
      } else {
        cArgs[i] = args[i];
      }
    }
  }
  var ret = func.apply(null, cArgs);
  function onDone(ret) {
    if (stack !== 0) stackRestore(stack);
    return convertReturnValue(ret);
  }

  ret = onDone(ret);
  return ret;
}

/** @param {string=} returnType
    @param {Array=} argTypes
    @param {Object=} opts */
function cwrap(ident, returnType, argTypes, opts) {
  return function() {
    return ccall(ident, returnType, argTypes, arguments, opts);
  }
}

// We used to include malloc/free by default in the past. Show a helpful error in
// builds with assertions.

var ALLOC_NORMAL = 0; // Tries to use _malloc()
var ALLOC_STACK = 1; // Lives for the duration of the current function call

// allocate(): This is for internal use. You can use it yourself as well, but the interface
//             is a little tricky (see docs right below). The reason is that it is optimized
//             for multiple syntaxes to save space in generated code. So you should
//             normally not use allocate(), and instead allocate memory using _malloc(),
//             initialize it with setValue(), and so forth.
// @slab: An array of data.
// @allocator: How to allocate memory, see ALLOC_*
/** @type {function((Uint8Array|Array<number>), number)} */
function allocate(slab, allocator) {
  var ret;
  assert(typeof allocator === 'number', 'allocate no longer takes a type argument')
  assert(typeof slab !== 'number', 'allocate no longer takes a number as arg0')

  if (allocator == ALLOC_STACK) {
    ret = stackAlloc(slab.length);
  } else {
    ret = _malloc(slab.length);
  }

  if (slab.subarray || slab.slice) {
    HEAPU8.set(/** @type {!Uint8Array} */(slab), ret);
  } else {
    HEAPU8.set(new Uint8Array(slab), ret);
  }
  return ret;
}

// include: runtime_strings.js


// runtime_strings.js: Strings related runtime functions that are part of both MINIMAL_RUNTIME and regular runtime.

// Given a pointer 'ptr' to a null-terminated UTF8-encoded string in the given array that contains uint8 values, returns
// a copy of that string as a Javascript String object.

var UTF8Decoder = typeof TextDecoder !== 'undefined' ? new TextDecoder('utf8') : undefined;

/**
 * @param {number} idx
 * @param {number=} maxBytesToRead
 * @return {string}
 */
function UTF8ArrayToString(heap, idx, maxBytesToRead) {
  var endIdx = idx + maxBytesToRead;
  var endPtr = idx;
  // TextDecoder needs to know the byte length in advance, it doesn't stop on null terminator by itself.
  // Also, use the length info to avoid running tiny strings through TextDecoder, since .subarray() allocates garbage.
  // (As a tiny code save trick, compare endPtr against endIdx using a negation, so that undefined means Infinity)
  while (heap[endPtr] && !(endPtr >= endIdx)) ++endPtr;

  if (endPtr - idx > 16 && heap.subarray && UTF8Decoder) {
    return UTF8Decoder.decode(heap.subarray(idx, endPtr));
  } else {
    var str = '';
    // If building with TextDecoder, we have already computed the string length above, so test loop end condition against that
    while (idx < endPtr) {
      // For UTF8 byte structure, see:
      // http://en.wikipedia.org/wiki/UTF-8#Description
      // https://www.ietf.org/rfc/rfc2279.txt
      // https://tools.ietf.org/html/rfc3629
      var u0 = heap[idx++];
      if (!(u0 & 0x80)) { str += String.fromCharCode(u0); continue; }
      var u1 = heap[idx++] & 63;
      if ((u0 & 0xE0) == 0xC0) { str += String.fromCharCode(((u0 & 31) << 6) | u1); continue; }
      var u2 = heap[idx++] & 63;
      if ((u0 & 0xF0) == 0xE0) {
        u0 = ((u0 & 15) << 12) | (u1 << 6) | u2;
      } else {
        if ((u0 & 0xF8) != 0xF0) warnOnce('Invalid UTF-8 leading byte 0x' + u0.toString(16) + ' encountered when deserializing a UTF-8 string in wasm memory to a JS string!');
        u0 = ((u0 & 7) << 18) | (u1 << 12) | (u2 << 6) | (heap[idx++] & 63);
      }

      if (u0 < 0x10000) {
        str += String.fromCharCode(u0);
      } else {
        var ch = u0 - 0x10000;
        str += String.fromCharCode(0xD800 | (ch >> 10), 0xDC00 | (ch & 0x3FF));
      }
    }
  }
  return str;
}

// Given a pointer 'ptr' to a null-terminated UTF8-encoded string in the emscripten HEAP, returns a
// copy of that string as a Javascript String object.
// maxBytesToRead: an optional length that specifies the maximum number of bytes to read. You can omit
//                 this parameter to scan the string until the first \0 byte. If maxBytesToRead is
//                 passed, and the string at [ptr, ptr+maxBytesToReadr[ contains a null byte in the
//                 middle, then the string will cut short at that byte index (i.e. maxBytesToRead will
//                 not produce a string of exact length [ptr, ptr+maxBytesToRead[)
//                 N.B. mixing frequent uses of UTF8ToString() with and without maxBytesToRead may
//                 throw JS JIT optimizations off, so it is worth to consider consistently using one
//                 style or the other.
/**
 * @param {number} ptr
 * @param {number=} maxBytesToRead
 * @return {string}
 */
function UTF8ToString(ptr, maxBytesToRead) {
  return ptr ? UTF8ArrayToString(HEAPU8, ptr, maxBytesToRead) : '';
}

// Copies the given Javascript String object 'str' to the given byte array at address 'outIdx',
// encoded in UTF8 form and null-terminated. The copy will require at most str.length*4+1 bytes of space in the HEAP.
// Use the function lengthBytesUTF8 to compute the exact number of bytes (excluding null terminator) that this function will write.
// Parameters:
//   str: the Javascript string to copy.
//   heap: the array to copy to. Each index in this array is assumed to be one 8-byte element.
//   outIdx: The starting offset in the array to begin the copying.
//   maxBytesToWrite: The maximum number of bytes this function can write to the array.
//                    This count should include the null terminator,
//                    i.e. if maxBytesToWrite=1, only the null terminator will be written and nothing else.
//                    maxBytesToWrite=0 does not write any bytes to the output, not even the null terminator.
// Returns the number of bytes written, EXCLUDING the null terminator.

function stringToUTF8Array(str, heap, outIdx, maxBytesToWrite) {
  if (!(maxBytesToWrite > 0)) // Parameter maxBytesToWrite is not optional. Negative values, 0, null, undefined and false each don't write out any bytes.
    return 0;

  var startIdx = outIdx;
  var endIdx = outIdx + maxBytesToWrite - 1; // -1 for string null terminator.
  for (var i = 0; i < str.length; ++i) {
    // Gotcha: charCodeAt returns a 16-bit word that is a UTF-16 encoded code unit, not a Unicode code point of the character! So decode UTF16->UTF32->UTF8.
    // See http://unicode.org/faq/utf_bom.html#utf16-3
    // For UTF8 byte structure, see http://en.wikipedia.org/wiki/UTF-8#Description and https://www.ietf.org/rfc/rfc2279.txt and https://tools.ietf.org/html/rfc3629
    var u = str.charCodeAt(i); // possibly a lead surrogate
    if (u >= 0xD800 && u <= 0xDFFF) {
      var u1 = str.charCodeAt(++i);
      u = 0x10000 + ((u & 0x3FF) << 10) | (u1 & 0x3FF);
    }
    if (u <= 0x7F) {
      if (outIdx >= endIdx) break;
      heap[outIdx++] = u;
    } else if (u <= 0x7FF) {
      if (outIdx + 1 >= endIdx) break;
      heap[outIdx++] = 0xC0 | (u >> 6);
      heap[outIdx++] = 0x80 | (u & 63);
    } else if (u <= 0xFFFF) {
      if (outIdx + 2 >= endIdx) break;
      heap[outIdx++] = 0xE0 | (u >> 12);
      heap[outIdx++] = 0x80 | ((u >> 6) & 63);
      heap[outIdx++] = 0x80 | (u & 63);
    } else {
      if (outIdx + 3 >= endIdx) break;
      if (u > 0x10FFFF) warnOnce('Invalid Unicode code point 0x' + u.toString(16) + ' encountered when serializing a JS string to a UTF-8 string in wasm memory! (Valid unicode code points should be in range 0-0x10FFFF).');
      heap[outIdx++] = 0xF0 | (u >> 18);
      heap[outIdx++] = 0x80 | ((u >> 12) & 63);
      heap[outIdx++] = 0x80 | ((u >> 6) & 63);
      heap[outIdx++] = 0x80 | (u & 63);
    }
  }
  // Null-terminate the pointer to the buffer.
  heap[outIdx] = 0;
  return outIdx - startIdx;
}

// Copies the given Javascript String object 'str' to the emscripten HEAP at address 'outPtr',
// null-terminated and encoded in UTF8 form. The copy will require at most str.length*4+1 bytes of space in the HEAP.
// Use the function lengthBytesUTF8 to compute the exact number of bytes (excluding null terminator) that this function will write.
// Returns the number of bytes written, EXCLUDING the null terminator.

function stringToUTF8(str, outPtr, maxBytesToWrite) {
  assert(typeof maxBytesToWrite == 'number', 'stringToUTF8(str, outPtr, maxBytesToWrite) is missing the third parameter that specifies the length of the output buffer!');
  return stringToUTF8Array(str, HEAPU8,outPtr, maxBytesToWrite);
}

// Returns the number of bytes the given Javascript string takes if encoded as a UTF8 byte array, EXCLUDING the null terminator byte.
function lengthBytesUTF8(str) {
  var len = 0;
  for (var i = 0; i < str.length; ++i) {
    // Gotcha: charCodeAt returns a 16-bit word that is a UTF-16 encoded code unit, not a Unicode code point of the character! So decode UTF16->UTF32->UTF8.
    // See http://unicode.org/faq/utf_bom.html#utf16-3
    var u = str.charCodeAt(i); // possibly a lead surrogate
    if (u >= 0xD800 && u <= 0xDFFF) u = 0x10000 + ((u & 0x3FF) << 10) | (str.charCodeAt(++i) & 0x3FF);
    if (u <= 0x7F) ++len;
    else if (u <= 0x7FF) len += 2;
    else if (u <= 0xFFFF) len += 3;
    else len += 4;
  }
  return len;
}

// end include: runtime_strings.js
// include: runtime_strings_extra.js


// runtime_strings_extra.js: Strings related runtime functions that are available only in regular runtime.

// Given a pointer 'ptr' to a null-terminated ASCII-encoded string in the emscripten HEAP, returns
// a copy of that string as a Javascript String object.

function AsciiToString(ptr) {
  var str = '';
  while (1) {
    var ch = HEAPU8[((ptr++)>>0)];
    if (!ch) return str;
    str += String.fromCharCode(ch);
  }
}

// Copies the given Javascript String object 'str' to the emscripten HEAP at address 'outPtr',
// null-terminated and encoded in ASCII form. The copy will require at most str.length+1 bytes of space in the HEAP.

function stringToAscii(str, outPtr) {
  return writeAsciiToMemory(str, outPtr, false);
}

// Given a pointer 'ptr' to a null-terminated UTF16LE-encoded string in the emscripten HEAP, returns
// a copy of that string as a Javascript String object.

var UTF16Decoder = typeof TextDecoder !== 'undefined' ? new TextDecoder('utf-16le') : undefined;

function UTF16ToString(ptr, maxBytesToRead) {
  assert(ptr % 2 == 0, 'Pointer passed to UTF16ToString must be aligned to two bytes!');
  var endPtr = ptr;
  // TextDecoder needs to know the byte length in advance, it doesn't stop on null terminator by itself.
  // Also, use the length info to avoid running tiny strings through TextDecoder, since .subarray() allocates garbage.
  var idx = endPtr >> 1;
  var maxIdx = idx + maxBytesToRead / 2;
  // If maxBytesToRead is not passed explicitly, it will be undefined, and this
  // will always evaluate to true. This saves on code size.
  while (!(idx >= maxIdx) && HEAPU16[idx]) ++idx;
  endPtr = idx << 1;

  if (endPtr - ptr > 32 && UTF16Decoder) {
    return UTF16Decoder.decode(HEAPU8.subarray(ptr, endPtr));
  } else {
    var str = '';

    // If maxBytesToRead is not passed explicitly, it will be undefined, and the for-loop's condition
    // will always evaluate to true. The loop is then terminated on the first null char.
    for (var i = 0; !(i >= maxBytesToRead / 2); ++i) {
      var codeUnit = HEAP16[(((ptr)+(i*2))>>1)];
      if (codeUnit == 0) break;
      // fromCharCode constructs a character from a UTF-16 code unit, so we can pass the UTF16 string right through.
      str += String.fromCharCode(codeUnit);
    }

    return str;
  }
}

// Copies the given Javascript String object 'str' to the emscripten HEAP at address 'outPtr',
// null-terminated and encoded in UTF16 form. The copy will require at most str.length*4+2 bytes of space in the HEAP.
// Use the function lengthBytesUTF16() to compute the exact number of bytes (excluding null terminator) that this function will write.
// Parameters:
//   str: the Javascript string to copy.
//   outPtr: Byte address in Emscripten HEAP where to write the string to.
//   maxBytesToWrite: The maximum number of bytes this function can write to the array. This count should include the null
//                    terminator, i.e. if maxBytesToWrite=2, only the null terminator will be written and nothing else.
//                    maxBytesToWrite<2 does not write any bytes to the output, not even the null terminator.
// Returns the number of bytes written, EXCLUDING the null terminator.

function stringToUTF16(str, outPtr, maxBytesToWrite) {
  assert(outPtr % 2 == 0, 'Pointer passed to stringToUTF16 must be aligned to two bytes!');
  assert(typeof maxBytesToWrite == 'number', 'stringToUTF16(str, outPtr, maxBytesToWrite) is missing the third parameter that specifies the length of the output buffer!');
  // Backwards compatibility: if max bytes is not specified, assume unsafe unbounded write is allowed.
  if (maxBytesToWrite === undefined) {
    maxBytesToWrite = 0x7FFFFFFF;
  }
  if (maxBytesToWrite < 2) return 0;
  maxBytesToWrite -= 2; // Null terminator.
  var startPtr = outPtr;
  var numCharsToWrite = (maxBytesToWrite < str.length*2) ? (maxBytesToWrite / 2) : str.length;
  for (var i = 0; i < numCharsToWrite; ++i) {
    // charCodeAt returns a UTF-16 encoded code unit, so it can be directly written to the HEAP.
    var codeUnit = str.charCodeAt(i); // possibly a lead surrogate
    HEAP16[((outPtr)>>1)] = codeUnit;
    outPtr += 2;
  }
  // Null-terminate the pointer to the HEAP.
  HEAP16[((outPtr)>>1)] = 0;
  return outPtr - startPtr;
}

// Returns the number of bytes the given Javascript string takes if encoded as a UTF16 byte array, EXCLUDING the null terminator byte.

function lengthBytesUTF16(str) {
  return str.length*2;
}

function UTF32ToString(ptr, maxBytesToRead) {
  assert(ptr % 4 == 0, 'Pointer passed to UTF32ToString must be aligned to four bytes!');
  var i = 0;

  var str = '';
  // If maxBytesToRead is not passed explicitly, it will be undefined, and this
  // will always evaluate to true. This saves on code size.
  while (!(i >= maxBytesToRead / 4)) {
    var utf32 = HEAP32[(((ptr)+(i*4))>>2)];
    if (utf32 == 0) break;
    ++i;
    // Gotcha: fromCharCode constructs a character from a UTF-16 encoded code (pair), not from a Unicode code point! So encode the code point to UTF-16 for constructing.
    // See http://unicode.org/faq/utf_bom.html#utf16-3
    if (utf32 >= 0x10000) {
      var ch = utf32 - 0x10000;
      str += String.fromCharCode(0xD800 | (ch >> 10), 0xDC00 | (ch & 0x3FF));
    } else {
      str += String.fromCharCode(utf32);
    }
  }
  return str;
}

// Copies the given Javascript String object 'str' to the emscripten HEAP at address 'outPtr',
// null-terminated and encoded in UTF32 form. The copy will require at most str.length*4+4 bytes of space in the HEAP.
// Use the function lengthBytesUTF32() to compute the exact number of bytes (excluding null terminator) that this function will write.
// Parameters:
//   str: the Javascript string to copy.
//   outPtr: Byte address in Emscripten HEAP where to write the string to.
//   maxBytesToWrite: The maximum number of bytes this function can write to the array. This count should include the null
//                    terminator, i.e. if maxBytesToWrite=4, only the null terminator will be written and nothing else.
//                    maxBytesToWrite<4 does not write any bytes to the output, not even the null terminator.
// Returns the number of bytes written, EXCLUDING the null terminator.

function stringToUTF32(str, outPtr, maxBytesToWrite) {
  assert(outPtr % 4 == 0, 'Pointer passed to stringToUTF32 must be aligned to four bytes!');
  assert(typeof maxBytesToWrite == 'number', 'stringToUTF32(str, outPtr, maxBytesToWrite) is missing the third parameter that specifies the length of the output buffer!');
  // Backwards compatibility: if max bytes is not specified, assume unsafe unbounded write is allowed.
  if (maxBytesToWrite === undefined) {
    maxBytesToWrite = 0x7FFFFFFF;
  }
  if (maxBytesToWrite < 4) return 0;
  var startPtr = outPtr;
  var endPtr = startPtr + maxBytesToWrite - 4;
  for (var i = 0; i < str.length; ++i) {
    // Gotcha: charCodeAt returns a 16-bit word that is a UTF-16 encoded code unit, not a Unicode code point of the character! We must decode the string to UTF-32 to the heap.
    // See http://unicode.org/faq/utf_bom.html#utf16-3
    var codeUnit = str.charCodeAt(i); // possibly a lead surrogate
    if (codeUnit >= 0xD800 && codeUnit <= 0xDFFF) {
      var trailSurrogate = str.charCodeAt(++i);
      codeUnit = 0x10000 + ((codeUnit & 0x3FF) << 10) | (trailSurrogate & 0x3FF);
    }
    HEAP32[((outPtr)>>2)] = codeUnit;
    outPtr += 4;
    if (outPtr + 4 > endPtr) break;
  }
  // Null-terminate the pointer to the HEAP.
  HEAP32[((outPtr)>>2)] = 0;
  return outPtr - startPtr;
}

// Returns the number of bytes the given Javascript string takes if encoded as a UTF16 byte array, EXCLUDING the null terminator byte.

function lengthBytesUTF32(str) {
  var len = 0;
  for (var i = 0; i < str.length; ++i) {
    // Gotcha: charCodeAt returns a 16-bit word that is a UTF-16 encoded code unit, not a Unicode code point of the character! We must decode the string to UTF-32 to the heap.
    // See http://unicode.org/faq/utf_bom.html#utf16-3
    var codeUnit = str.charCodeAt(i);
    if (codeUnit >= 0xD800 && codeUnit <= 0xDFFF) ++i; // possibly a lead surrogate, so skip over the tail surrogate.
    len += 4;
  }

  return len;
}

// Allocate heap space for a JS string, and write it there.
// It is the responsibility of the caller to free() that memory.
function allocateUTF8(str) {
  var size = lengthBytesUTF8(str) + 1;
  var ret = _malloc(size);
  if (ret) stringToUTF8Array(str, HEAP8, ret, size);
  return ret;
}

// Allocate stack space for a JS string, and write it there.
function allocateUTF8OnStack(str) {
  var size = lengthBytesUTF8(str) + 1;
  var ret = stackAlloc(size);
  stringToUTF8Array(str, HEAP8, ret, size);
  return ret;
}

// Deprecated: This function should not be called because it is unsafe and does not provide
// a maximum length limit of how many bytes it is allowed to write. Prefer calling the
// function stringToUTF8Array() instead, which takes in a maximum length that can be used
// to be secure from out of bounds writes.
/** @deprecated
    @param {boolean=} dontAddNull */
function writeStringToMemory(string, buffer, dontAddNull) {
  warnOnce('writeStringToMemory is deprecated and should not be called! Use stringToUTF8() instead!');

  var /** @type {number} */ lastChar, /** @type {number} */ end;
  if (dontAddNull) {
    // stringToUTF8Array always appends null. If we don't want to do that, remember the
    // character that existed at the location where the null will be placed, and restore
    // that after the write (below).
    end = buffer + lengthBytesUTF8(string);
    lastChar = HEAP8[end];
  }
  stringToUTF8(string, buffer, Infinity);
  if (dontAddNull) HEAP8[end] = lastChar; // Restore the value under the null character.
}

function writeArrayToMemory(array, buffer) {
  assert(array.length >= 0, 'writeArrayToMemory array must have a length (should be an array or typed array)')
  HEAP8.set(array, buffer);
}

/** @param {boolean=} dontAddNull */
function writeAsciiToMemory(str, buffer, dontAddNull) {
  for (var i = 0; i < str.length; ++i) {
    assert(str.charCodeAt(i) === str.charCodeAt(i)&0xff);
    HEAP8[((buffer++)>>0)] = str.charCodeAt(i);
  }
  // Null-terminate the pointer to the HEAP.
  if (!dontAddNull) HEAP8[((buffer)>>0)] = 0;
}

// end include: runtime_strings_extra.js
// Memory management

function alignUp(x, multiple) {
  if (x % multiple > 0) {
    x += multiple - (x % multiple);
  }
  return x;
}

var HEAP,
/** @type {ArrayBuffer} */
  buffer,
/** @type {Int8Array} */
  HEAP8,
/** @type {Uint8Array} */
  HEAPU8,
/** @type {Int16Array} */
  HEAP16,
/** @type {Uint16Array} */
  HEAPU16,
/** @type {Int32Array} */
  HEAP32,
/** @type {Uint32Array} */
  HEAPU32,
/** @type {Float32Array} */
  HEAPF32,
/** @type {Float64Array} */
  HEAPF64;

function updateGlobalBufferAndViews(buf) {
  buffer = buf;
  Module['HEAP8'] = HEAP8 = new Int8Array(buf);
  Module['HEAP16'] = HEAP16 = new Int16Array(buf);
  Module['HEAP32'] = HEAP32 = new Int32Array(buf);
  Module['HEAPU8'] = HEAPU8 = new Uint8Array(buf);
  Module['HEAPU16'] = HEAPU16 = new Uint16Array(buf);
  Module['HEAPU32'] = HEAPU32 = new Uint32Array(buf);
  Module['HEAPF32'] = HEAPF32 = new Float32Array(buf);
  Module['HEAPF64'] = HEAPF64 = new Float64Array(buf);
}

var TOTAL_STACK = 5242880;
if (Module['TOTAL_STACK']) assert(TOTAL_STACK === Module['TOTAL_STACK'], 'the stack size can no longer be determined at runtime')

var INITIAL_MEMORY = Module['INITIAL_MEMORY'] || 16777216;
if (!Object.getOwnPropertyDescriptor(Module, 'INITIAL_MEMORY')) {
  Object.defineProperty(Module, 'INITIAL_MEMORY', {
    configurable: true,
    get: function() {
      abort('Module.INITIAL_MEMORY has been replaced with plain INITIAL_MEMORY (the initial value can be provided on Module, but after startup the value is only looked for on a local variable of that name)')
    }
  });
}

assert(INITIAL_MEMORY >= TOTAL_STACK, 'INITIAL_MEMORY should be larger than TOTAL_STACK, was ' + INITIAL_MEMORY + '! (TOTAL_STACK=' + TOTAL_STACK + ')');

// check for full engine support (use string 'subarray' to avoid closure compiler confusion)
assert(typeof Int32Array !== 'undefined' && typeof Float64Array !== 'undefined' && Int32Array.prototype.subarray !== undefined && Int32Array.prototype.set !== undefined,
       'JS engine does not provide full typed array support');

// If memory is defined in wasm, the user can't provide it.
assert(!Module['wasmMemory'], 'Use of `wasmMemory` detected.  Use -s IMPORTED_MEMORY to define wasmMemory externally');
assert(INITIAL_MEMORY == 16777216, 'Detected runtime INITIAL_MEMORY setting.  Use -s IMPORTED_MEMORY to define wasmMemory dynamically');

// include: runtime_init_table.js
// In regular non-RELOCATABLE mode the table is exported
// from the wasm module and this will be assigned once
// the exports are available.
var wasmTable;

// end include: runtime_init_table.js
// include: runtime_stack_check.js


// Initializes the stack cookie. Called at the startup of main and at the startup of each thread in pthreads mode.
function writeStackCookie() {
  var max = _emscripten_stack_get_end();
  assert((max & 3) == 0);
  // The stack grows downwards
  HEAPU32[(max >> 2)+1] = 0x2135467;
  HEAPU32[(max >> 2)+2] = 0x89BACDFE;
  // Also test the global address 0 for integrity.
  HEAP32[0] = 0x63736d65; /* 'emsc' */
}

function checkStackCookie() {
  if (ABORT) return;
  var max = _emscripten_stack_get_end();
  var cookie1 = HEAPU32[(max >> 2)+1];
  var cookie2 = HEAPU32[(max >> 2)+2];
  if (cookie1 != 0x2135467 || cookie2 != 0x89BACDFE) {
    abort('Stack overflow! Stack cookie has been overwritten, expected hex dwords 0x89BACDFE and 0x2135467, but received 0x' + cookie2.toString(16) + ' ' + cookie1.toString(16));
  }
  // Also test the global address 0 for integrity.
  if (HEAP32[0] !== 0x63736d65 /* 'emsc' */) abort('Runtime error: The application has corrupted its heap memory area (address zero)!');
}

// end include: runtime_stack_check.js
// include: runtime_assertions.js


// Endianness check
(function() {
  var h16 = new Int16Array(1);
  var h8 = new Int8Array(h16.buffer);
  h16[0] = 0x6373;
  if (h8[0] !== 0x73 || h8[1] !== 0x63) throw 'Runtime error: expected the system to be little-endian! (Run with -s SUPPORT_BIG_ENDIAN=1 to bypass)';
})();

// end include: runtime_assertions.js
var __ATPRERUN__  = []; // functions called before the runtime is initialized
var __ATINIT__    = []; // functions called during startup
var __ATEXIT__    = []; // functions called during shutdown
var __ATPOSTRUN__ = []; // functions called after the main() is called

var runtimeInitialized = false;
var runtimeExited = false;
var runtimeKeepaliveCounter = 0;

function keepRuntimeAlive() {
  return noExitRuntime || runtimeKeepaliveCounter > 0;
}

function preRun() {

  if (Module['preRun']) {
    if (typeof Module['preRun'] == 'function') Module['preRun'] = [Module['preRun']];
    while (Module['preRun'].length) {
      addOnPreRun(Module['preRun'].shift());
    }
  }

  callRuntimeCallbacks(__ATPRERUN__);
}

function initRuntime() {
  checkStackCookie();
  assert(!runtimeInitialized);
  runtimeInitialized = true;

  
  callRuntimeCallbacks(__ATINIT__);
}

function exitRuntime() {
  checkStackCookie();
  runtimeExited = true;
}

function postRun() {
  checkStackCookie();

  if (Module['postRun']) {
    if (typeof Module['postRun'] == 'function') Module['postRun'] = [Module['postRun']];
    while (Module['postRun'].length) {
      addOnPostRun(Module['postRun'].shift());
    }
  }

  callRuntimeCallbacks(__ATPOSTRUN__);
}

function addOnPreRun(cb) {
  __ATPRERUN__.unshift(cb);
}

function addOnInit(cb) {
  __ATINIT__.unshift(cb);
}

function addOnExit(cb) {
}

function addOnPostRun(cb) {
  __ATPOSTRUN__.unshift(cb);
}

// include: runtime_math.js


// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math/imul

// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math/fround

// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math/clz32

// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math/trunc

assert(Math.imul, 'This browser does not support Math.imul(), build with LEGACY_VM_SUPPORT or POLYFILL_OLD_MATH_FUNCTIONS to add in a polyfill');
assert(Math.fround, 'This browser does not support Math.fround(), build with LEGACY_VM_SUPPORT or POLYFILL_OLD_MATH_FUNCTIONS to add in a polyfill');
assert(Math.clz32, 'This browser does not support Math.clz32(), build with LEGACY_VM_SUPPORT or POLYFILL_OLD_MATH_FUNCTIONS to add in a polyfill');
assert(Math.trunc, 'This browser does not support Math.trunc(), build with LEGACY_VM_SUPPORT or POLYFILL_OLD_MATH_FUNCTIONS to add in a polyfill');

// end include: runtime_math.js
// A counter of dependencies for calling run(). If we need to
// do asynchronous work before running, increment this and
// decrement it. Incrementing must happen in a place like
// Module.preRun (used by emcc to add file preloading).
// Note that you can add dependencies in preRun, even though
// it happens right before run - run will be postponed until
// the dependencies are met.
var runDependencies = 0;
var runDependencyWatcher = null;
var dependenciesFulfilled = null; // overridden to take different actions when all run dependencies are fulfilled
var runDependencyTracking = {};

function getUniqueRunDependency(id) {
  var orig = id;
  while (1) {
    if (!runDependencyTracking[id]) return id;
    id = orig + Math.random();
  }
}

function addRunDependency(id) {
  runDependencies++;

  if (Module['monitorRunDependencies']) {
    Module['monitorRunDependencies'](runDependencies);
  }

  if (id) {
    assert(!runDependencyTracking[id]);
    runDependencyTracking[id] = 1;
    if (runDependencyWatcher === null && typeof setInterval !== 'undefined') {
      // Check for missing dependencies every few seconds
      runDependencyWatcher = setInterval(function() {
        if (ABORT) {
          clearInterval(runDependencyWatcher);
          runDependencyWatcher = null;
          return;
        }
        var shown = false;
        for (var dep in runDependencyTracking) {
          if (!shown) {
            shown = true;
            err('still waiting on run dependencies:');
          }
          err('dependency: ' + dep);
        }
        if (shown) {
          err('(end of list)');
        }
      }, 10000);
    }
  } else {
    err('warning: run dependency added without ID');
  }
}

function removeRunDependency(id) {
  runDependencies--;

  if (Module['monitorRunDependencies']) {
    Module['monitorRunDependencies'](runDependencies);
  }

  if (id) {
    assert(runDependencyTracking[id]);
    delete runDependencyTracking[id];
  } else {
    err('warning: run dependency removed without ID');
  }
  if (runDependencies == 0) {
    if (runDependencyWatcher !== null) {
      clearInterval(runDependencyWatcher);
      runDependencyWatcher = null;
    }
    if (dependenciesFulfilled) {
      var callback = dependenciesFulfilled;
      dependenciesFulfilled = null;
      callback(); // can add another dependenciesFulfilled
    }
  }
}

Module["preloadedImages"] = {}; // maps url to image data
Module["preloadedAudios"] = {}; // maps url to audio data

/** @param {string|number=} what */
function abort(what) {
  {
    if (Module['onAbort']) {
      Module['onAbort'](what);
    }
  }

  what = 'Aborted(' + what + ')';
  // TODO(sbc): Should we remove printing and leave it up to whoever
  // catches the exception?
  err(what);

  ABORT = true;
  EXITSTATUS = 1;

  // Use a wasm runtime error, because a JS error might be seen as a foreign
  // exception, which means we'd run destructors on it. We need the error to
  // simply make the program stop.
  var e = new WebAssembly.RuntimeError(what);

  // Throw the error whether or not MODULARIZE is set because abort is used
  // in code paths apart from instantiation where an exception is expected
  // to be thrown when abort is called.
  throw e;
}

// {{MEM_INITIALIZER}}

// include: memoryprofiler.js


// end include: memoryprofiler.js
// show errors on likely calls to FS when it was not included
var FS = {
  error: function() {
    abort('Filesystem support (FS) was not included. The problem is that you are using files from JS, but files were not used from C/C++, so filesystem support was not auto-included. You can force-include filesystem support with  -s FORCE_FILESYSTEM=1');
  },
  init: function() { FS.error() },
  createDataFile: function() { FS.error() },
  createPreloadedFile: function() { FS.error() },
  createLazyFile: function() { FS.error() },
  open: function() { FS.error() },
  mkdev: function() { FS.error() },
  registerDevice: function() { FS.error() },
  analyzePath: function() { FS.error() },
  loadFilesFromDB: function() { FS.error() },

  ErrnoError: function ErrnoError() { FS.error() },
};
Module['FS_createDataFile'] = FS.createDataFile;
Module['FS_createPreloadedFile'] = FS.createPreloadedFile;

// include: URIUtils.js


// Prefix of data URIs emitted by SINGLE_FILE and related options.
var dataURIPrefix = 'data:application/octet-stream;base64,';

// Indicates whether filename is a base64 data URI.
function isDataURI(filename) {
  // Prefix of data URIs emitted by SINGLE_FILE and related options.
  return filename.startsWith(dataURIPrefix);
}

// Indicates whether filename is delivered via file protocol (as opposed to http/https)
function isFileURI(filename) {
  return filename.startsWith('file://');
}

// end include: URIUtils.js
function createExportWrapper(name, fixedasm) {
  return function() {
    var displayName = name;
    var asm = fixedasm;
    if (!fixedasm) {
      asm = Module['asm'];
    }
    assert(runtimeInitialized, 'native function `' + displayName + '` called before runtime initialization');
    assert(!runtimeExited, 'native function `' + displayName + '` called after runtime exit (use NO_EXIT_RUNTIME to keep it alive after main() exits)');
    if (!asm[name]) {
      assert(asm[name], 'exported native function `' + displayName + '` not found');
    }
    return asm[name].apply(null, arguments);
  };
}

var wasmBinaryFile;
  wasmBinaryFile = 'data:application/octet-stream;base64,AGFzbQEAAAAB8oCAgAASYAF/AX9gAAF/YAJ/fwF/YAF/AGACf38AYAN/f38AYAN/f38Bf2AEf39/fwBgBX9/f39/AGAAAGAGf39/f39/AGAAAX5gBH9/f38Bf2ABfAF/YAN/f38BfGADf35/AX5gBX9/f35+AGAHf39/f39/fwAC6IWAgAAcA2Vudg1fZW12YWxfaW5jcmVmAAMDZW52DV9lbXZhbF9kZWNyZWYAAwNlbnYZX2VtYmluZF9yZWdpc3Rlcl9mdW5jdGlvbgAKA2VudhNfZW12YWxfZ2V0X3Byb3BlcnR5AAIDZW52DV9fYXNzZXJ0X2ZhaWwABwNlbnYRX2VtdmFsX25ld19vYmplY3QAAQNlbnYTX2VtdmFsX3NldF9wcm9wZXJ0eQAFA2VudglfZW12YWxfYXMADgNlbnYRX2VtdmFsX3Rha2VfdmFsdWUAAgNlbnYSX2VtdmFsX25ld19jc3RyaW5nAAADZW52Fl9lbXZhbF9ydW5fZGVzdHJ1Y3RvcnMAAwNlbnYYX19jeGFfYWxsb2NhdGVfZXhjZXB0aW9uAAADZW52C19fY3hhX3Rocm93AAUDZW52F19lbXZhbF9jYWxsX3ZvaWRfbWV0aG9kAAcDZW52GF9lbXZhbF9nZXRfbWV0aG9kX2NhbGxlcgACA2VudhBfZW12YWxfbmV3X2FycmF5AAEDZW52FV9lbWJpbmRfcmVnaXN0ZXJfdm9pZAAEA2VudhVfZW1iaW5kX3JlZ2lzdGVyX2Jvb2wACANlbnYbX2VtYmluZF9yZWdpc3Rlcl9zdGRfc3RyaW5nAAQDZW52HF9lbWJpbmRfcmVnaXN0ZXJfc3RkX3dzdHJpbmcABQNlbnYWX2VtYmluZF9yZWdpc3Rlcl9lbXZhbAAEA2VudhhfZW1iaW5kX3JlZ2lzdGVyX2ludGVnZXIACANlbnYWX2VtYmluZF9yZWdpc3Rlcl9mbG9hdAAFA2VudhxfZW1iaW5kX3JlZ2lzdGVyX21lbW9yeV92aWV3AAUDZW52BWFib3J0AAkDZW52FmVtc2NyaXB0ZW5fcmVzaXplX2hlYXAAAANlbnYVZW1zY3JpcHRlbl9tZW1jcHlfYmlnAAYDZW52F19lbWJpbmRfcmVnaXN0ZXJfYmlnaW50ABED64WAgADpBQkEAgQABQQFBAUFBwME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bGUAdm9pZABkYXRhAGVtc2NyaXB0ZW46Om1lbW9yeV92aWV3PHNob3J0PgBlbXNjcmlwdGVuOjptZW1vcnlfdmlldzx1bnNpZ25lZCBzaG9ydD4AZW1zY3JpcHRlbjo6bWVtb3J5X3ZpZXc8aW50PgBlbXNjcmlwdGVuOjptZW1vcnlfdmlldzx1bnNpZ25lZCBpbnQ+AGVtc2NyaXB0ZW46Om1lbW9yeV92aWV3PGZsb2F0PgBlbXNjcmlwdGVuOjptZW1vcnlfdmlldzx1aW50OF90PgBlbXNjcmlwdGVuOjptZW1vcnlfdmlldzxpbnQ4X3Q+AGVtc2NyaXB0ZW46Om1lbW9yeV92aWV3PHVpbnQxNl90PgBlbXNjcmlwdGVuOjptZW1vcnlfdmlldzxpbnQxNl90PgBlbXNjcmlwdGVuOjptZW1vcnlfdmlldzx1aW50MzJfdD4AZW1zY3JpcHRlbjo6bWVtb3J5X3ZpZXc8aW50MzJfdD4AZW1zY3JpcHRlbjo6bWVtb3J5X3ZpZXc8Y2hhcj4AZW1zY3JpcHRlbjo6bWVtb3J5X3ZpZXc8dW5zaWduZWQgY2hhcj4Ac3RkOjpiYXNpY19zdHJpbmc8dW5zaWduZWQgY2hhcj4AZW1zY3JpcHRlbjo6bWVtb3J5X3ZpZXc8c2lnbmVkIGNoYXI+AGVtc2NyaXB0ZW46Om1lbW9yeV92aWV3PGxvbmc+AGVtc2NyaXB0ZW46Om1lbW9yeV92aWV3PHVuc2lnbmVkIGxvbmc+AGVtc2NyaXB0ZW46Om1lbW9yeV92aWV3PGRvdWJsZT4AdHJhbnNwb3NlX2kzMgB1dGlsczo6aXNlcXVhbChvbGRfbnVtZWwsbmV3X251bWVsKQBvcGVyYXRvcigpAAAAANgOAABOMTBlbXNjcmlwdGVuMTFtZW1vcnlfdmlld0lpRUUAABgPAADQCAAAYA4AABQJAABOMTBlbXNjcmlwdGVuM3ZhbEUAABgPAAAACQAATjEwZW1zY3JpcHRlbjExbWVtb3J5X3ZpZXdJbUVFAAAYDwAAHAkAAAAAAAAAAAAAAAAAAGAOAAC0DgAAYA4AANgOAAAAAAAAAAAAAAAAAAAUCQAAFAkAAGlpaQBOU3QzX18yMTJiYXNpY19zdHJpbmdJY05TXzExY2hhcl90cmFpdHNJY0VFTlNfOWFsbG9jYXRvckljRUVFRQBOU3QzX18yMjFfX2Jhc2ljX3N0cmluZ19jb21tb25JTGIxRUVFAAAAABgPAAC3CQAAnA8AAHgJAAAAAAAAAQAAAOAJAAAAAAAATlN0M19fMjEyYmFzaWNfc3RyaW5nSWhOU18xMWNoYXJfdHJhaXRzSWhFRU5TXzlhbGxvY2F0b3JJaEVFRUUAAJwPAAAACgAAAAAAAAEAAADgCQAAAAAAAE5TdDNfXzIxMmJhc2ljX3N0cmluZ0l3TlNfMTFjaGFyX3RyYWl0c0l3RUVOU185YWxsb2NhdG9ySXdFRUVFAACcDwAAWAoAAAAAAAABAAAA4AkAAAAAAABOU3QzX18yMTJiYXNpY19zdHJpbmdJRHNOU18xMWNoYXJfdHJhaXRzSURzRUVOU185YWxsb2NhdG9ySURzRUVFRQAAAJwPAACwCgAAAAAAAAEAAADgCQAAAAAAAE5TdDNfXzIxMmJhc2ljX3N0cmluZ0lEaU5TXzExY2hhcl90cmFpdHNJRGlFRU5TXzlhbGxvY2F0b3JJRGlFRUVFAAAAnA8AAAwLAAAAAAAAAQAAAOAJAAAAAAAATjEwZW1zY3JpcHRlbjExbWVtb3J5X3ZpZXdJY0VFAAAYDwAAaAsAAE4xMGVtc2NyaXB0ZW4xMW1lbW9yeV92aWV3SWFFRQAAGA8AAJALAABOMTBlbXNjcmlwdGVuMTFtZW1vcnlfdmlld0loRUUAABgPAAC4CwAATjEwZW1zY3JpcHRlbjExbWVtb3J5X3ZpZXdJc0VFAAAYDwAA4AsAAE4xMGVtc2NyaXB0ZW4xMW1lbW9yeV92aWV3SXRFRQAAGA8AAAgMAABOMTBlbXNjcmlwdGVuMTFtZW1vcnlfdmlld0lqRUUAABgPAAAwDAAATjEwZW1zY3JpcHRlbjExbWVtb3J5X3ZpZXdJbEVFAAAYDwAAWAwAAE4xMGVtc2NyaXB0ZW4xMW1lbW9yeV92aWV3SWZFRQAAGA8AAIAMAABOMTBlbXNjcmlwdGVuMTFtZW1vcnlfdmlld0lkRUUAABgPAACoDAAAAAAAAPQMAAAGAAAABwAAAAgAAABTdDlleGNlcHRpb24AAAAAGA8AAOQMAAAAAAAAIA0AAAQAAAAJAAAACgAAAFN0MTFsb2dpY19lcnJvcgBADwAAEA0AAPQMAAAAAAAAVA0AAAQAAAALAAAACgAAAFN0MTJsZW5ndGhfZXJyb3IAAAAAQA8AAEANAAAgDQAAAAAAAIgNAAAEAAAADAAAAAoAAABTdDEyb3V0X29mX3JhbmdlAAAAAEAPAAB0DQAAIA0AAFN0OXR5cGVfaW5mbwAAAAAYDwAAlA0AAE4xMF9fY3h4YWJpdjExNl9fc2hpbV90eXBlX2luZm9FAAAAAEAPAACsDQAApA0AAE4xMF9fY3h4YWJpdjExN19fY2xhc3NfdHlwZV9pbmZvRQAAAEAPAADcDQAA0A0AAAAAAABQDgAADQAAAA4AAAAPAAAAEAAAABEAAABOMTBfX2N4eGFiaXYxMjNfX2Z1bmRhbWVudGFsX3R5cGVfaW5mb0UAQA8AACgOAADQDQAAdgAAABQOAABcDgAAYgAAABQOAABoDgAAYwAAABQOAAB0DgAAaAAAABQOAACADgAAYQAAABQOAACMDgAAcwAAABQOAACYDgAAdAAAABQOAACkDgAAaQAAABQOAACwDgAAagAAABQOAAC8DgAAbAAAABQOAADIDgAAbQAAABQOAADUDgAAeAAAABQOAADgDgAAeQAAABQOAADsDgAAZgAAABQOAAD4DgAAZAAAABQOAAAEDwAAAAAAAAAOAAANAAAAEgAAAA8AAAAQAAAAEwAAABQAAAAVAAAAFgAAAAAAAACIDwAADQAAABcAAAAPAAAAEAAAABMAAAAYAAAAGQAAABoAAABOMTBfX2N4eGFiaXYxMjBfX3NpX2NsYXNzX3R5cGVfaW5mb0UAAAAAQA8AAGAPAAAADgAAAAAAAOQPAAANAAAAGwAAAA8AAAAQAAAAEwAAABwAAAAdAAAAHgAAAE4xMF9fY3h4YWJpdjEyMV9fdm1pX2NsYXNzX3R5cGVfaW5mb0UAAABADwAAvA8AAAAOAAAAQfAfCwQgElAA';
  if (!isDataURI(wasmBinaryFile)) {
    wasmBinaryFile = locateFile(wasmBinaryFile);
  }

function getBinary(file) {
  try {
    if (file == wasmBinaryFile && wasmBinary) {
      return new Uint8Array(wasmBinary);
    }
    var binary = tryParseAsDataURI(file);
    if (binary) {
      return binary;
    }
    if (readBinary) {
      return readBinary(file);
    } else {
      throw "both async and sync fetching of the wasm failed";
    }
  }
  catch (err) {
    abort(err);
  }
}

function getBinaryPromise() {
  // If we don't have the binary yet, try to to load it asynchronously.
  // Fetch has some additional restrictions over XHR, like it can't be used on a file:// url.
  // See https://github.com/github/fetch/pull/92#issuecomment-140665932
  // Cordova or Electron apps are typically loaded from a file:// url.
  // So use fetch if it is available and the url is not a file, otherwise fall back to XHR.
  if (!wasmBinary && (ENVIRONMENT_IS_WEB || ENVIRONMENT_IS_WORKER)) {
    if (typeof fetch === 'function'
      && !isFileURI(wasmBinaryFile)
    ) {
      return fetch(wasmBinaryFile, { credentials: 'same-origin' }).then(function(response) {
        if (!response['ok']) {
          throw "failed to load wasm binary file at '" + wasmBinaryFile + "'";
        }
        return response['arrayBuffer']();
      }).catch(function () {
          return getBinary(wasmBinaryFile);
      });
    }
    else {
      if (readAsync) {
        // fetch is not available or url is file => try XHR (readAsync uses XHR internally)
        return new Promise(function(resolve, reject) {
          readAsync(wasmBinaryFile, function(response) { resolve(new Uint8Array(/** @type{!ArrayBuffer} */(response))) }, reject)
        });
      }
    }
  }

  // Otherwise, getBinary should be able to get it synchronously
  return Promise.resolve().then(function() { return getBinary(wasmBinaryFile); });
}

// Create the wasm instance.
// Receives the wasm imports, returns the exports.
function createWasm() {
  // prepare imports
  var info = {
    'env': asmLibraryArg,
    'wasi_snapshot_preview1': asmLibraryArg,
  };
  // Load the wasm module and create an instance of using native support in the JS engine.
  // handle a generated wasm instance, receiving its exports and
  // performing other necessary setup
  /** @param {WebAssembly.Module=} module*/
  function receiveInstance(instance, module) {
    var exports = instance.exports;

    Module['asm'] = exports;

    wasmMemory = Module['asm']['memory'];
    assert(wasmMemory, "memory not found in wasm exports");
    // This assertion doesn't hold when emscripten is run in --post-link
    // mode.
    // TODO(sbc): Read INITIAL_MEMORY out of the wasm file in post-link mode.
    //assert(wasmMemory.buffer.byteLength === 16777216);
    updateGlobalBufferAndViews(wasmMemory.buffer);

    wasmTable = Module['asm']['__indirect_function_table'];
    assert(wasmTable, "table not found in wasm exports");

    addOnInit(Module['asm']['__wasm_call_ctors']);

    removeRunDependency('wasm-instantiate');
  }
  // we can't run yet (except in a pthread, where we have a custom sync instantiator)
  addRunDependency('wasm-instantiate');

  // Prefer streaming instantiation if available.
  // Async compilation can be confusing when an error on the page overwrites Module
  // (for example, if the order of elements is wrong, and the one defining Module is
  // later), so we save Module and check it later.
  var trueModule = Module;
  function receiveInstantiationResult(result) {
    // 'result' is a ResultObject object which has both the module and instance.
    // receiveInstance() will swap in the exports (to Module.asm) so they can be called
    assert(Module === trueModule, 'the Module object should not be replaced during async compilation - perhaps the order of HTML elements is wrong?');
    trueModule = null;
    // TODO: Due to Closure regression https://github.com/google/closure-compiler/issues/3193, the above line no longer optimizes out down to the following line.
    // When the regression is fixed, can restore the above USE_PTHREADS-enabled path.
    receiveInstance(result['instance']);
  }

  function instantiateArrayBuffer(receiver) {
    return getBinaryPromise().then(function(binary) {
      return WebAssembly.instantiate(binary, info);
    }).then(function (instance) {
      return instance;
    }).then(receiver, function(reason) {
      err('failed to asynchronously prepare wasm: ' + reason);

      // Warn on some common problems.
      if (isFileURI(wasmBinaryFile)) {
        err('warning: Loading from a file URI (' + wasmBinaryFile + ') is not supported in most browsers. See https://emscripten.org/docs/getting_started/FAQ.html#how-do-i-run-a-local-webserver-for-testing-why-does-my-program-stall-in-downloading-or-preparing');
      }
      abort(reason);
    });
  }

  function instantiateAsync() {
    if (!wasmBinary &&
        typeof WebAssembly.instantiateStreaming === 'function' &&
        !isDataURI(wasmBinaryFile) &&
        // Don't use streaming for file:// delivered objects in a webview, fetch them synchronously.
        !isFileURI(wasmBinaryFile) &&
        typeof fetch === 'function') {
      return fetch(wasmBinaryFile, { credentials: 'same-origin' }).then(function (response) {
        var result = WebAssembly.instantiateStreaming(response, info);

        return result.then(
          receiveInstantiationResult,
          function(reason) {
            // We expect the most common failure cause to be a bad MIME type for the binary,
            // in which case falling back to ArrayBuffer instantiation should work.
            err('wasm streaming compile failed: ' + reason);
            err('falling back to ArrayBuffer instantiation');
            return instantiateArrayBuffer(receiveInstantiationResult);
          });
      });
    } else {
      return instantiateArrayBuffer(receiveInstantiationResult);
    }
  }

  // User shell pages can write their own Module.instantiateWasm = function(imports, successCallback) callback
  // to manually instantiate the Wasm module themselves. This allows pages to run the instantiation parallel
  // to any other async startup actions they are performing.
  if (Module['instantiateWasm']) {
    try {
      var exports = Module['instantiateWasm'](info, receiveInstance);
      return exports;
    } catch(e) {
      err('Module.instantiateWasm callback failed with error: ' + e);
      return false;
    }
  }

  instantiateAsync();
  return {}; // no exports yet; we'll fill them in later
}

// Globals used by JS i64 conversions (see makeSetValue)
var tempDouble;
var tempI64;

// === Body ===

var ASM_CONSTS = {
  
};






  function callRuntimeCallbacks(callbacks) {
      while (callbacks.length > 0) {
        var callback = callbacks.shift();
        if (typeof callback == 'function') {
          callback(Module); // Pass the module as the first argument.
          continue;
        }
        var func = callback.func;
        if (typeof func === 'number') {
          if (callback.arg === undefined) {
            wasmTable.get(func)();
          } else {
            wasmTable.get(func)(callback.arg);
          }
        } else {
          func(callback.arg === undefined ? null : callback.arg);
        }
      }
    }

  function demangle(func) {
      warnOnce('warning: build with  -s DEMANGLE_SUPPORT=1  to link in libcxxabi demangling');
      return func;
    }

  function demangleAll(text) {
      var regex =
        /\b_Z[\w\d_]+/g;
      return text.replace(regex,
        function(x) {
          var y = demangle(x);
          return x === y ? x : (y + ' [' + x + ']');
        });
    }

  function handleException(e) {
      // Certain exception types we do not treat as errors since they are used for
      // internal control flow.
      // 1. ExitStatus, which is thrown by exit()
      // 2. "unwind", which is thrown by emscripten_unwind_to_js_event_loop() and others
      //    that wish to return to JS event loop.
      if (e instanceof ExitStatus || e == 'unwind') {
        return EXITSTATUS;
      }
      quit_(1, e);
    }

  function jsStackTrace() {
      var error = new Error();
      if (!error.stack) {
        // IE10+ special cases: It does have callstack info, but it is only populated if an Error object is thrown,
        // so try that as a special-case.
        try {
          throw new Error();
        } catch(e) {
          error = e;
        }
        if (!error.stack) {
          return '(no stack trace available)';
        }
      }
      return error.stack.toString();
    }

  function stackTrace() {
      var js = jsStackTrace();
      if (Module['extraStackTrace']) js += '\n' + Module['extraStackTrace']();
      return demangleAll(js);
    }

  function ___assert_fail(condition, filename, line, func) {
      abort('Assertion failed: ' + UTF8ToString(condition) + ', at: ' + [filename ? UTF8ToString(filename) : 'unknown filename', line, func ? UTF8ToString(func) : 'unknown function']);
    }

  function ___cxa_allocate_exception(size) {
      // Thrown object is prepended by exception metadata block
      return _malloc(size + 16) + 16;
    }

  function ExceptionInfo(excPtr) {
      this.excPtr = excPtr;
      this.ptr = excPtr - 16;
  
      this.set_type = function(type) {
        HEAP32[(((this.ptr)+(4))>>2)] = type;
      };
  
      this.get_type = function() {
        return HEAP32[(((this.ptr)+(4))>>2)];
      };
  
      this.set_destructor = function(destructor) {
        HEAP32[(((this.ptr)+(8))>>2)] = destructor;
      };
  
      this.get_destructor = function() {
        return HEAP32[(((this.ptr)+(8))>>2)];
      };
  
      this.set_refcount = function(refcount) {
        HEAP32[((this.ptr)>>2)] = refcount;
      };
  
      this.set_caught = function (caught) {
        caught = caught ? 1 : 0;
        HEAP8[(((this.ptr)+(12))>>0)] = caught;
      };
  
      this.get_caught = function () {
        return HEAP8[(((this.ptr)+(12))>>0)] != 0;
      };
  
      this.set_rethrown = function (rethrown) {
        rethrown = rethrown ? 1 : 0;
        HEAP8[(((this.ptr)+(13))>>0)] = rethrown;
      };
  
      this.get_rethrown = function () {
        return HEAP8[(((this.ptr)+(13))>>0)] != 0;
      };
  
      // Initialize native structure fields. Should be called once after allocated.
      this.init = function(type, destructor) {
        this.set_type(type);
        this.set_destructor(destructor);
        this.set_refcount(0);
        this.set_caught(false);
        this.set_rethrown(false);
      }
  
      this.add_ref = function() {
        var value = HEAP32[((this.ptr)>>2)];
        HEAP32[((this.ptr)>>2)] = value + 1;
      };
  
      // Returns true if last reference released.
      this.release_ref = function() {
        var prev = HEAP32[((this.ptr)>>2)];
        HEAP32[((this.ptr)>>2)] = prev - 1;
        assert(prev > 0);
        return prev === 1;
      };
    }
  
  var exceptionLast = 0;
  
  var uncaughtExceptionCount = 0;
  function ___cxa_throw(ptr, type, destructor) {
      var info = new ExceptionInfo(ptr);
      // Initialize ExceptionInfo content after it was allocated in __cxa_allocate_exception.
      info.init(type, destructor);
      exceptionLast = ptr;
      uncaughtExceptionCount++;
      throw ptr + " - Exception catching is disabled, this exception cannot be caught. Compile with -s NO_DISABLE_EXCEPTION_CATCHING or -s EXCEPTION_CATCHING_ALLOWED=[..] to catch.";
    }

  function __embind_register_bigint(primitiveType, name, size, minRange, maxRange) {}

  function getShiftFromSize(size) {
      switch (size) {
          case 1: return 0;
          case 2: return 1;
          case 4: return 2;
          case 8: return 3;
          default:
              throw new TypeError('Unknown type size: ' + size);
      }
    }
  
  function embind_init_charCodes() {
      var codes = new Array(256);
      for (var i = 0; i < 256; ++i) {
          codes[i] = String.fromCharCode(i);
      }
      embind_charCodes = codes;
    }
  var embind_charCodes = undefined;
  function readLatin1String(ptr) {
      var ret = "";
      var c = ptr;
      while (HEAPU8[c]) {
          ret += embind_charCodes[HEAPU8[c++]];
      }
      return ret;
    }
  
  var awaitingDependencies = {};
  
  var registeredTypes = {};
  
  var typeDependencies = {};
  
  var char_0 = 48;
  
  var char_9 = 57;
  function makeLegalFunctionName(name) {
      if (undefined === name) {
          return '_unknown';
      }
      name = name.replace(/[^a-zA-Z0-9_]/g, '$');
      var f = name.charCodeAt(0);
      if (f >= char_0 && f <= char_9) {
          return '_' + name;
      } else {
          return name;
      }
    }
  function createNamedFunction(name, body) {
      name = makeLegalFunctionName(name);
      /*jshint evil:true*/
      return new Function(
          "body",
          "return function " + name + "() {\n" +
          "    \"use strict\";" +
          "    return body.apply(this, arguments);\n" +
          "};\n"
      )(body);
    }
  function extendError(baseErrorType, errorName) {
      var errorClass = createNamedFunction(errorName, function(message) {
          this.name = errorName;
          this.message = message;
  
          var stack = (new Error(message)).stack;
          if (stack !== undefined) {
              this.stack = this.toString() + '\n' +
                  stack.replace(/^Error(:[^\n]*)?\n/, '');
          }
      });
      errorClass.prototype = Object.create(baseErrorType.prototype);
      errorClass.prototype.constructor = errorClass;
      errorClass.prototype.toString = function() {
          if (this.message === undefined) {
              return this.name;
          } else {
              return this.name + ': ' + this.message;
          }
      };
  
      return errorClass;
    }
  var BindingError = undefined;
  function throwBindingError(message) {
      throw new BindingError(message);
    }
  
  var InternalError = undefined;
  function throwInternalError(message) {
      throw new InternalError(message);
    }
  function whenDependentTypesAreResolved(myTypes, dependentTypes, getTypeConverters) {
      myTypes.forEach(function(type) {
          typeDependencies[type] = dependentTypes;
      });
  
      function onComplete(typeConverters) {
          var myTypeConverters = getTypeConverters(typeConverters);
          if (myTypeConverters.length !== myTypes.length) {
              throwInternalError('Mismatched type converter count');
          }
          for (var i = 0; i < myTypes.length; ++i) {
              registerType(myTypes[i], myTypeConverters[i]);
          }
      }
  
      var typeConverters = new Array(dependentTypes.length);
      var unregisteredTypes = [];
      var registered = 0;
      dependentTypes.forEach(function(dt, i) {
          if (registeredTypes.hasOwnProperty(dt)) {
              typeConverters[i] = registeredTypes[dt];
          } else {
              unregisteredTypes.push(dt);
              if (!awaitingDependencies.hasOwnProperty(dt)) {
                  awaitingDependencies[dt] = [];
              }
              awaitingDependencies[dt].push(function() {
                  typeConverters[i] = registeredTypes[dt];
                  ++registered;
                  if (registered === unregisteredTypes.length) {
                      onComplete(typeConverters);
                  }
              });
          }
      });
      if (0 === unregisteredTypes.length) {
          onComplete(typeConverters);
      }
    }
  /** @param {Object=} options */
  function registerType(rawType, registeredInstance, options) {
      options = options || {};
  
      if (!('argPackAdvance' in registeredInstance)) {
          throw new TypeError('registerType registeredInstance requires argPackAdvance');
      }
  
      var name = registeredInstance.name;
      if (!rawType) {
          throwBindingError('type "' + name + '" must have a positive integer typeid pointer');
      }
      if (registeredTypes.hasOwnProperty(rawType)) {
          if (options.ignoreDuplicateRegistrations) {
              return;
          } else {
              throwBindingError("Cannot register type '" + name + "' twice");
          }
      }
  
      registeredTypes[rawType] = registeredInstance;
      delete typeDependencies[rawType];
  
      if (awaitingDependencies.hasOwnProperty(rawType)) {
          var callbacks = awaitingDependencies[rawType];
          delete awaitingDependencies[rawType];
          callbacks.forEach(function(cb) {
              cb();
          });
      }
    }
  function __embind_register_bool(rawType, name, size, trueValue, falseValue) {
      var shift = getShiftFromSize(size);
  
      name = readLatin1String(name);
      registerType(rawType, {
          name: name,
          'fromWireType': function(wt) {
              // ambiguous emscripten ABI: sometimes return values are
              // true or false, and sometimes integers (0 or 1)
              return !!wt;
          },
          'toWireType': function(destructors, o) {
              return o ? trueValue : falseValue;
          },
          'argPackAdvance': 8,
          'readValueFromPointer': function(pointer) {
              // TODO: if heap is fixed (like in asm.js) this could be executed outside
              var heap;
              if (size === 1) {
                  heap = HEAP8;
              } else if (size === 2) {
                  heap = HEAP16;
              } else if (size === 4) {
                  heap = HEAP32;
              } else {
                  throw new TypeError("Unknown boolean type size: " + name);
              }
              return this['fromWireType'](heap[pointer >> shift]);
          },
          destructorFunction: null, // This type does not need a destructor
      });
    }

  var emval_free_list = [];
  
  var emval_handle_array = [{},{value:undefined},{value:null},{value:true},{value:false}];
  function __emval_decref(handle) {
      if (handle > 4 && 0 === --emval_handle_array[handle].refcount) {
          emval_handle_array[handle] = undefined;
          emval_free_list.push(handle);
      }
    }
  
  function count_emval_handles() {
      var count = 0;
      for (var i = 5; i < emval_handle_array.length; ++i) {
          if (emval_handle_array[i] !== undefined) {
              ++count;
          }
      }
      return count;
    }
  
  function get_first_emval() {
      for (var i = 5; i < emval_handle_array.length; ++i) {
          if (emval_handle_array[i] !== undefined) {
              return emval_handle_array[i];
          }
      }
      return null;
    }
  function init_emval() {
      Module['count_emval_handles'] = count_emval_handles;
      Module['get_first_emval'] = get_first_emval;
    }
  function __emval_register(value) {
      switch (value) {
        case undefined :{ return 1; }
        case null :{ return 2; }
        case true :{ return 3; }
        case false :{ return 4; }
        default:{
          var handle = emval_free_list.length ?
              emval_free_list.pop() :
              emval_handle_array.length;
  
          emval_handle_array[handle] = {refcount: 1, value: value};
          return handle;
          }
        }
    }
  
  function simpleReadValueFromPointer(pointer) {
      return this['fromWireType'](HEAPU32[pointer >> 2]);
    }
  function __embind_register_emval(rawType, name) {
      name = readLatin1String(name);
      registerType(rawType, {
          name: name,
          'fromWireType': function(handle) {
              var rv = emval_handle_array[handle].value;
              __emval_decref(handle);
              return rv;
          },
          'toWireType': function(destructors, value) {
              return __emval_register(value);
          },
          'argPackAdvance': 8,
          'readValueFromPointer': simpleReadValueFromPointer,
          destructorFunction: null, // This type does not need a destructor
  
          // TODO: do we need a deleteObject here?  write a test where
          // emval is passed into JS via an interface
      });
    }

  function _embind_repr(v) {
      if (v === null) {
          return 'null';
      }
      var t = typeof v;
      if (t === 'object' || t === 'array' || t === 'function') {
          return v.toString();
      } else {
          return '' + v;
      }
    }
  
  function floatReadValueFromPointer(name, shift) {
      switch (shift) {
          case 2: return function(pointer) {
              return this['fromWireType'](HEAPF32[pointer >> 2]);
          };
          case 3: return function(pointer) {
              return this['fromWireType'](HEAPF64[pointer >> 3]);
          };
          default:
              throw new TypeError("Unknown float type: " + name);
      }
    }
  function __embind_register_float(rawType, name, size) {
      var shift = getShiftFromSize(size);
      name = readLatin1String(name);
      registerType(rawType, {
          name: name,
          'fromWireType': function(value) {
              return value;
          },
          'toWireType': function(destructors, value) {
              // todo: Here we have an opportunity for -O3 level "unsafe" optimizations: we could
              // avoid the following if() and assume value is of proper type.
              if (typeof value !== "number" && typeof value !== "boolean") {
                  throw new TypeError('Cannot convert "' + _embind_repr(value) + '" to ' + this.name);
              }
              return value;
          },
          'argPackAdvance': 8,
          'readValueFromPointer': floatReadValueFromPointer(name, shift),
          destructorFunction: null, // This type does not need a destructor
      });
    }

  function new_(constructor, argumentList) {
      if (!(constructor instanceof Function)) {
          throw new TypeError('new_ called with constructor type ' + typeof(constructor) + " which is not a function");
      }
  
      /*
       * Previously, the following line was just:
  
       function dummy() {};
  
       * Unfortunately, Chrome was preserving 'dummy' as the object's name, even though at creation, the 'dummy' has the
       * correct constructor name.  Thus, objects created with IMVU.new would show up in the debugger as 'dummy', which
       * isn't very helpful.  Using IMVU.createNamedFunction addresses the issue.  Doublely-unfortunately, there's no way
       * to write a test for this behavior.  -NRD 2013.02.22
       */
      var dummy = createNamedFunction(constructor.name || 'unknownFunctionName', function(){});
      dummy.prototype = constructor.prototype;
      var obj = new dummy;
  
      var r = constructor.apply(obj, argumentList);
      return (r instanceof Object) ? r : obj;
    }
  
  function runDestructors(destructors) {
      while (destructors.length) {
          var ptr = destructors.pop();
          var del = destructors.pop();
          del(ptr);
      }
    }
  function craftInvokerFunction(humanName, argTypes, classType, cppInvokerFunc, cppTargetFunc) {
      // humanName: a human-readable string name for the function to be generated.
      // argTypes: An array that contains the embind type objects for all types in the function signature.
      //    argTypes[0] is the type object for the function return value.
      //    argTypes[1] is the type object for function this object/class type, or null if not crafting an invoker for a class method.
      //    argTypes[2...] are the actual function parameters.
      // classType: The embind type object for the class to be bound, or null if this is not a method of a class.
      // cppInvokerFunc: JS Function object to the C++-side function that interops into C++ code.
      // cppTargetFunc: Function pointer (an integer to FUNCTION_TABLE) to the target C++ function the cppInvokerFunc will end up calling.
      var argCount = argTypes.length;
  
      if (argCount < 2) {
          throwBindingError("argTypes array size mismatch! Must at least get return value and 'this' types!");
      }
  
      var isClassMethodFunc = (argTypes[1] !== null && classType !== null);
  
      // Free functions with signature "void function()" do not need an invoker that marshalls between wire types.
  // TODO: This omits argument count check - enable only at -O3 or similar.
  //    if (ENABLE_UNSAFE_OPTS && argCount == 2 && argTypes[0].name == "void" && !isClassMethodFunc) {
  //       return FUNCTION_TABLE[fn];
  //    }
  
      // Determine if we need to use a dynamic stack to store the destructors for the function parameters.
      // TODO: Remove this completely once all function invokers are being dynamically generated.
      var needsDestructorStack = false;
  
      for (var i = 1; i < argTypes.length; ++i) { // Skip return value at index 0 - it's not deleted here.
          if (argTypes[i] !== null && argTypes[i].destructorFunction === undefined) { // The type does not define a destructor function - must use dynamic stack
              needsDestructorStack = true;
              break;
          }
      }
  
      var returns = (argTypes[0].name !== "void");
  
      var argsList = "";
      var argsListWired = "";
      for (var i = 0; i < argCount - 2; ++i) {
          argsList += (i!==0?", ":"")+"arg"+i;
          argsListWired += (i!==0?", ":"")+"arg"+i+"Wired";
      }
  
      var invokerFnBody =
          "return function "+makeLegalFunctionName(humanName)+"("+argsList+") {\n" +
          "if (arguments.length !== "+(argCount - 2)+") {\n" +
              "throwBindingError('function "+humanName+" called with ' + arguments.length + ' arguments, expected "+(argCount - 2)+" args!');\n" +
          "}\n";
  
      if (needsDestructorStack) {
          invokerFnBody +=
              "var destructors = [];\n";
      }
  
      var dtorStack = needsDestructorStack ? "destructors" : "null";
      var args1 = ["throwBindingError", "invoker", "fn", "runDestructors", "retType", "classParam"];
      var args2 = [throwBindingError, cppInvokerFunc, cppTargetFunc, runDestructors, argTypes[0], argTypes[1]];
  
      if (isClassMethodFunc) {
          invokerFnBody += "var thisWired = classParam.toWireType("+dtorStack+", this);\n";
      }
  
      for (var i = 0; i < argCount - 2; ++i) {
          invokerFnBody += "var arg"+i+"Wired = argType"+i+".toWireType("+dtorStack+", arg"+i+"); // "+argTypes[i+2].name+"\n";
          args1.push("argType"+i);
          args2.push(argTypes[i+2]);
      }
  
      if (isClassMethodFunc) {
          argsListWired = "thisWired" + (argsListWired.length > 0 ? ", " : "") + argsListWired;
      }
  
      invokerFnBody +=
          (returns?"var rv = ":"") + "invoker(fn"+(argsListWired.length>0?", ":"")+argsListWired+");\n";
  
      if (needsDestructorStack) {
          invokerFnBody += "runDestructors(destructors);\n";
      } else {
          for (var i = isClassMethodFunc?1:2; i < argTypes.length; ++i) { // Skip return value at index 0 - it's not deleted here. Also skip class type if not a method.
              var paramName = (i === 1 ? "thisWired" : ("arg"+(i - 2)+"Wired"));
              if (argTypes[i].destructorFunction !== null) {
                  invokerFnBody += paramName+"_dtor("+paramName+"); // "+argTypes[i].name+"\n";
                  args1.push(paramName+"_dtor");
                  args2.push(argTypes[i].destructorFunction);
              }
          }
      }
  
      if (returns) {
          invokerFnBody += "var ret = retType.fromWireType(rv);\n" +
                           "return ret;\n";
      } else {
      }
  
      invokerFnBody += "}\n";
  
      args1.push(invokerFnBody);
  
      var invokerFunction = new_(Function, args1).apply(null, args2);
      return invokerFunction;
    }
  
  function ensureOverloadTable(proto, methodName, humanName) {
      if (undefined === proto[methodName].overloadTable) {
          var prevFunc = proto[methodName];
          // Inject an overload resolver function that routes to the appropriate overload based on the number of arguments.
          proto[methodName] = function() {
              // TODO This check can be removed in -O3 level "unsafe" optimizations.
              if (!proto[methodName].overloadTable.hasOwnProperty(arguments.length)) {
                  throwBindingError("Function '" + humanName + "' called with an invalid number of arguments (" + arguments.length + ") - expects one of (" + proto[methodName].overloadTable + ")!");
              }
              return proto[methodName].overloadTable[arguments.length].apply(this, arguments);
          };
          // Move the previous function into the overload table.
          proto[methodName].overloadTable = [];
          proto[methodName].overloadTable[prevFunc.argCount] = prevFunc;
      }
    }
  /** @param {number=} numArguments */
  function exposePublicSymbol(name, value, numArguments) {
      if (Module.hasOwnProperty(name)) {
          if (undefined === numArguments || (undefined !== Module[name].overloadTable && undefined !== Module[name].overloadTable[numArguments])) {
              throwBindingError("Cannot register public name '" + name + "' twice");
          }
  
          // We are exposing a function with the same name as an existing function. Create an overload table and a function selector
          // that routes between the two.
          ensureOverloadTable(Module, name, name);
          if (Module.hasOwnProperty(numArguments)) {
              throwBindingError("Cannot register multiple overloads of a function with the same number of arguments (" + numArguments + ")!");
          }
          // Add the new function into the overload table.
          Module[name].overloadTable[numArguments] = value;
      }
      else {
          Module[name] = value;
          if (undefined !== numArguments) {
              Module[name].numArguments = numArguments;
          }
      }
    }
  
  function heap32VectorToArray(count, firstElement) {
      var array = [];
      for (var i = 0; i < count; i++) {
          array.push(HEAP32[(firstElement >> 2) + i]);
      }
      return array;
    }
  
  /** @param {number=} numArguments */
  function replacePublicSymbol(name, value, numArguments) {
      if (!Module.hasOwnProperty(name)) {
          throwInternalError('Replacing nonexistant public symbol');
      }
      // If there's an overload table for this symbol, replace the symbol in the overload table instead.
      if (undefined !== Module[name].overloadTable && undefined !== numArguments) {
          Module[name].overloadTable[numArguments] = value;
      }
      else {
          Module[name] = value;
          Module[name].argCount = numArguments;
      }
    }
  
  function dynCallLegacy(sig, ptr, args) {
      assert(('dynCall_' + sig) in Module, 'bad function pointer type - no table for sig \'' + sig + '\'');
      if (args && args.length) {
        // j (64-bit integer) must be passed in as two numbers [low 32, high 32].
        assert(args.length === sig.substring(1).replace(/j/g, '--').length);
      } else {
        assert(sig.length == 1);
      }
      var f = Module["dynCall_" + sig];
      return args && args.length ? f.apply(null, [ptr].concat(args)) : f.call(null, ptr);
    }
  function dynCall(sig, ptr, args) {
      // Without WASM_BIGINT support we cannot directly call function with i64 as
      // part of thier signature, so we rely the dynCall functions generated by
      // wasm-emscripten-finalize
      if (sig.includes('j')) {
        return dynCallLegacy(sig, ptr, args);
      }
      assert(wasmTable.get(ptr), 'missing table entry in dynCall: ' + ptr);
      return wasmTable.get(ptr).apply(null, args)
    }
  function getDynCaller(sig, ptr) {
      assert(sig.includes('j'), 'getDynCaller should only be called with i64 sigs')
      var argCache = [];
      return function() {
        argCache.length = arguments.length;
        for (var i = 0; i < arguments.length; i++) {
          argCache[i] = arguments[i];
        }
        return dynCall(sig, ptr, argCache);
      };
    }
  function embind__requireFunction(signature, rawFunction) {
      signature = readLatin1String(signature);
  
      function makeDynCaller() {
        if (signature.includes('j')) {
          return getDynCaller(signature, rawFunction);
        }
        return wasmTable.get(rawFunction);
      }
  
      var fp = makeDynCaller();
      if (typeof fp !== "function") {
          throwBindingError("unknown function pointer with signature " + signature + ": " + rawFunction);
      }
      return fp;
    }
  
  var UnboundTypeError = undefined;
  
  function getTypeName(type) {
      var ptr = ___getTypeName(type);
      var rv = readLatin1String(ptr);
      _free(ptr);
      return rv;
    }
  function throwUnboundTypeError(message, types) {
      var unboundTypes = [];
      var seen = {};
      function visit(type) {
          if (seen[type]) {
              return;
          }
          if (registeredTypes[type]) {
              return;
          }
          if (typeDependencies[type]) {
              typeDependencies[type].forEach(visit);
              return;
          }
          unboundTypes.push(type);
          seen[type] = true;
      }
      types.forEach(visit);
  
      throw new UnboundTypeError(message + ': ' + unboundTypes.map(getTypeName).join([', ']));
    }
  function __embind_register_function(name, argCount, rawArgTypesAddr, signature, rawInvoker, fn) {
      var argTypes = heap32VectorToArray(argCount, rawArgTypesAddr);
      name = readLatin1String(name);
  
      rawInvoker = embind__requireFunction(signature, rawInvoker);
  
      exposePublicSymbol(name, function() {
          throwUnboundTypeError('Cannot call ' + name + ' due to unbound types', argTypes);
      }, argCount - 1);
  
      whenDependentTypesAreResolved([], argTypes, function(argTypes) {
          var invokerArgsArray = [argTypes[0] /* return value */, null /* no class 'this'*/].concat(argTypes.slice(1) /* actual params */);
          replacePublicSymbol(name, craftInvokerFunction(name, invokerArgsArray, null /* no class 'this'*/, rawInvoker, fn), argCount - 1);
          return [];
      });
    }

  function integerReadValueFromPointer(name, shift, signed) {
      // integers are quite common, so generate very specialized functions
      switch (shift) {
          case 0: return signed ?
              function readS8FromPointer(pointer) { return HEAP8[pointer]; } :
              function readU8FromPointer(pointer) { return HEAPU8[pointer]; };
          case 1: return signed ?
              function readS16FromPointer(pointer) { return HEAP16[pointer >> 1]; } :
              function readU16FromPointer(pointer) { return HEAPU16[pointer >> 1]; };
          case 2: return signed ?
              function readS32FromPointer(pointer) { return HEAP32[pointer >> 2]; } :
              function readU32FromPointer(pointer) { return HEAPU32[pointer >> 2]; };
          default:
              throw new TypeError("Unknown integer type: " + name);
      }
    }
  function __embind_register_integer(primitiveType, name, size, minRange, maxRange) {
      name = readLatin1String(name);
      if (maxRange === -1) { // LLVM doesn't have signed and unsigned 32-bit types, so u32 literals come out as 'i32 -1'. Always treat those as max u32.
          maxRange = 4294967295;
      }
  
      var shift = getShiftFromSize(size);
  
      var fromWireType = function(value) {
          return value;
      };
  
      if (minRange === 0) {
          var bitshift = 32 - 8*size;
          fromWireType = function(value) {
              return (value << bitshift) >>> bitshift;
          };
      }
  
      var isUnsignedType = (name.includes('unsigned'));
  
      registerType(primitiveType, {
          name: name,
          'fromWireType': fromWireType,
          'toWireType': function(destructors, value) {
              // todo: Here we have an opportunity for -O3 level "unsafe" optimizations: we could
              // avoid the following two if()s and assume value is of proper type.
              if (typeof value !== "number" && typeof value !== "boolean") {
                  throw new TypeError('Cannot convert "' + _embind_repr(value) + '" to ' + this.name);
              }
              if (value < minRange || value > maxRange) {
                  throw new TypeError('Passing a number "' + _embind_repr(value) + '" from JS side to C/C++ side to an argument of type "' + name + '", which is outside the valid range [' + minRange + ', ' + maxRange + ']!');
              }
              return isUnsignedType ? (value >>> 0) : (value | 0);
          },
          'argPackAdvance': 8,
          'readValueFromPointer': integerReadValueFromPointer(name, shift, minRange !== 0),
          destructorFunction: null, // This type does not need a destructor
      });
    }

  function __embind_register_memory_view(rawType, dataTypeIndex, name) {
      var typeMapping = [
          Int8Array,
          Uint8Array,
          Int16Array,
          Uint16Array,
          Int32Array,
          Uint32Array,
          Float32Array,
          Float64Array,
      ];
  
      var TA = typeMapping[dataTypeIndex];
  
      function decodeMemoryView(handle) {
          handle = handle >> 2;
          var heap = HEAPU32;
          var size = heap[handle]; // in elements
          var data = heap[handle + 1]; // byte offset into emscripten heap
          return new TA(buffer, data, size);
      }
  
      name = readLatin1String(name);
      registerType(rawType, {
          name: name,
          'fromWireType': decodeMemoryView,
          'argPackAdvance': 8,
          'readValueFromPointer': decodeMemoryView,
      }, {
          ignoreDuplicateRegistrations: true,
      });
    }

  function __embind_register_std_string(rawType, name) {
      name = readLatin1String(name);
      var stdStringIsUTF8
      //process only std::string bindings with UTF8 support, in contrast to e.g. std::basic_string<unsigned char>
      = (name === "std::string");
  
      registerType(rawType, {
          name: name,
          'fromWireType': function(value) {
              var length = HEAPU32[value >> 2];
  
              var str;
              if (stdStringIsUTF8) {
                  var decodeStartPtr = value + 4;
                  // Looping here to support possible embedded '0' bytes
                  for (var i = 0; i <= length; ++i) {
                      var currentBytePtr = value + 4 + i;
                      if (i == length || HEAPU8[currentBytePtr] == 0) {
                          var maxRead = currentBytePtr - decodeStartPtr;
                          var stringSegment = UTF8ToString(decodeStartPtr, maxRead);
                          if (str === undefined) {
                              str = stringSegment;
                          } else {
                              str += String.fromCharCode(0);
                              str += stringSegment;
                          }
                          decodeStartPtr = currentBytePtr + 1;
                      }
                  }
              } else {
                  var a = new Array(length);
                  for (var i = 0; i < length; ++i) {
                      a[i] = String.fromCharCode(HEAPU8[value + 4 + i]);
                  }
                  str = a.join('');
              }
  
              _free(value);
  
              return str;
          },
          'toWireType': function(destructors, value) {
              if (value instanceof ArrayBuffer) {
                  value = new Uint8Array(value);
              }
  
              var getLength;
              var valueIsOfTypeString = (typeof value === 'string');
  
              if (!(valueIsOfTypeString || value instanceof Uint8Array || value instanceof Uint8ClampedArray || value instanceof Int8Array)) {
                  throwBindingError('Cannot pass non-string to std::string');
              }
              if (stdStringIsUTF8 && valueIsOfTypeString) {
                  getLength = function() {return lengthBytesUTF8(value);};
              } else {
                  getLength = function() {return value.length;};
              }
  
              // assumes 4-byte alignment
              var length = getLength();
              var ptr = _malloc(4 + length + 1);
              HEAPU32[ptr >> 2] = length;
              if (stdStringIsUTF8 && valueIsOfTypeString) {
                  stringToUTF8(value, ptr + 4, length + 1);
              } else {
                  if (valueIsOfTypeString) {
                      for (var i = 0; i < length; ++i) {
                          var charCode = value.charCodeAt(i);
                          if (charCode > 255) {
                              _free(ptr);
                              throwBindingError('String has UTF-16 code units that do not fit in 8 bits');
                          }
                          HEAPU8[ptr + 4 + i] = charCode;
                      }
                  } else {
                      for (var i = 0; i < length; ++i) {
                          HEAPU8[ptr + 4 + i] = value[i];
                      }
                  }
              }
  
              if (destructors !== null) {
                  destructors.push(_free, ptr);
              }
              return ptr;
          },
          'argPackAdvance': 8,
          'readValueFromPointer': simpleReadValueFromPointer,
          destructorFunction: function(ptr) { _free(ptr); },
      });
    }

  function __embind_register_std_wstring(rawType, charSize, name) {
      name = readLatin1String(name);
      var decodeString, encodeString, getHeap, lengthBytesUTF, shift;
      if (charSize === 2) {
          decodeString = UTF16ToString;
          encodeString = stringToUTF16;
          lengthBytesUTF = lengthBytesUTF16;
          getHeap = function() { return HEAPU16; };
          shift = 1;
      } else if (charSize === 4) {
          decodeString = UTF32ToString;
          encodeString = stringToUTF32;
          lengthBytesUTF = lengthBytesUTF32;
          getHeap = function() { return HEAPU32; };
          shift = 2;
      }
      registerType(rawType, {
          name: name,
          'fromWireType': function(value) {
              // Code mostly taken from _embind_register_std_string fromWireType
              var length = HEAPU32[value >> 2];
              var HEAP = getHeap();
              var str;
  
              var decodeStartPtr = value + 4;
              // Looping here to support possible embedded '0' bytes
              for (var i = 0; i <= length; ++i) {
                  var currentBytePtr = value + 4 + i * charSize;
                  if (i == length || HEAP[currentBytePtr >> shift] == 0) {
                      var maxReadBytes = currentBytePtr - decodeStartPtr;
                      var stringSegment = decodeString(decodeStartPtr, maxReadBytes);
                      if (str === undefined) {
                          str = stringSegment;
                      } else {
                          str += String.fromCharCode(0);
                          str += stringSegment;
                      }
                      decodeStartPtr = currentBytePtr + charSize;
                  }
              }
  
              _free(value);
  
              return str;
          },
          'toWireType': function(destructors, value) {
              if (!(typeof value === 'string')) {
                  throwBindingError('Cannot pass non-string to C++ string type ' + name);
              }
  
              // assumes 4-byte alignment
              var length = lengthBytesUTF(value);
              var ptr = _malloc(4 + length + charSize);
              HEAPU32[ptr >> 2] = length >> shift;
  
              encodeString(value, ptr + 4, length + charSize);
  
              if (destructors !== null) {
                  destructors.push(_free, ptr);
              }
              return ptr;
          },
          'argPackAdvance': 8,
          'readValueFromPointer': simpleReadValueFromPointer,
          destructorFunction: function(ptr) { _free(ptr); },
      });
    }

  function __embind_register_void(rawType, name) {
      name = readLatin1String(name);
      registerType(rawType, {
          isVoid: true, // void return values can be optimized out sometimes
          name: name,
          'argPackAdvance': 0,
          'fromWireType': function() {
              return undefined;
          },
          'toWireType': function(destructors, o) {
              // TODO: assert if anything else is given?
              return undefined;
          },
      });
    }

  function requireHandle(handle) {
      if (!handle) {
          throwBindingError('Cannot use deleted val. handle = ' + handle);
      }
      return emval_handle_array[handle].value;
    }
  
  function requireRegisteredType(rawType, humanName) {
      var impl = registeredTypes[rawType];
      if (undefined === impl) {
          throwBindingError(humanName + " has unknown type " + getTypeName(rawType));
      }
      return impl;
    }
  function __emval_as(handle, returnType, destructorsRef) {
      handle = requireHandle(handle);
      returnType = requireRegisteredType(returnType, 'emval::as');
      var destructors = [];
      var rd = __emval_register(destructors);
      HEAP32[destructorsRef >> 2] = rd;
      return returnType['toWireType'](destructors, handle);
    }

  function __emval_allocateDestructors(destructorsRef) {
      var destructors = [];
      HEAP32[destructorsRef >> 2] = __emval_register(destructors);
      return destructors;
    }
  
  var emval_symbols = {};
  function getStringOrSymbol(address) {
      var symbol = emval_symbols[address];
      if (symbol === undefined) {
          return readLatin1String(address);
      } else {
          return symbol;
      }
    }
  
  var emval_methodCallers = [];
  function __emval_call_void_method(caller, handle, methodName, args) {
      caller = emval_methodCallers[caller];
      handle = requireHandle(handle);
      methodName = getStringOrSymbol(methodName);
      caller(handle, methodName, null, args);
    }


  function __emval_addMethodCaller(caller) {
      var id = emval_methodCallers.length;
      emval_methodCallers.push(caller);
      return id;
    }
  
  function __emval_lookupTypes(argCount, argTypes) {
      var a = new Array(argCount);
      for (var i = 0; i < argCount; ++i) {
          a[i] = requireRegisteredType(
              HEAP32[(argTypes >> 2) + i],
              "parameter " + i);
      }
      return a;
    }
  function __emval_get_method_caller(argCount, argTypes) {
      var types = __emval_lookupTypes(argCount, argTypes);
  
      var retType = types[0];
      var signatureName = retType.name + "_$" + types.slice(1).map(function (t) { return t.name; }).join("_") + "$";
  
      var params = ["retType"];
      var args = [retType];
  
      var argsList = ""; // 'arg0, arg1, arg2, ... , argN'
      for (var i = 0; i < argCount - 1; ++i) {
          argsList += (i !== 0 ? ", " : "") + "arg" + i;
          params.push("argType" + i);
          args.push(types[1 + i]);
      }
  
      var functionName = makeLegalFunctionName("methodCaller_" + signatureName);
      var functionBody =
          "return function " + functionName + "(handle, name, destructors, args) {\n";
  
      var offset = 0;
      for (var i = 0; i < argCount - 1; ++i) {
          functionBody +=
          "    var arg" + i + " = argType" + i + ".readValueFromPointer(args" + (offset ? ("+"+offset) : "") + ");\n";
          offset += types[i + 1]['argPackAdvance'];
      }
      functionBody +=
          "    var rv = handle[name](" + argsList + ");\n";
      for (var i = 0; i < argCount - 1; ++i) {
          if (types[i + 1]['deleteObject']) {
              functionBody +=
              "    argType" + i + ".deleteObject(arg" + i + ");\n";
          }
      }
      if (!retType.isVoid) {
          functionBody +=
          "    return retType.toWireType(destructors, rv);\n";
      }
      functionBody +=
          "};\n";
  
      params.push(functionBody);
      var invokerFunction = new_(Function, params).apply(null, args);
      return __emval_addMethodCaller(invokerFunction);
    }

  function __emval_get_property(handle, key) {
      handle = requireHandle(handle);
      key = requireHandle(key);
      return __emval_register(handle[key]);
    }

  function __emval_incref(handle) {
      if (handle > 4) {
          emval_handle_array[handle].refcount += 1;
      }
    }

  function __emval_new_array() {
      return __emval_register([]);
    }

  function __emval_new_cstring(v) {
      return __emval_register(getStringOrSymbol(v));
    }

  function __emval_new_object() {
      return __emval_register({});
    }

  function __emval_run_destructors(handle) {
      var destructors = emval_handle_array[handle].value;
      runDestructors(destructors);
      __emval_decref(handle);
    }

  function __emval_set_property(handle, key, value) {
      handle = requireHandle(handle);
      key = requireHandle(key);
      value = requireHandle(value);
      handle[key] = value;
    }

  function __emval_take_value(type, argv) {
      type = requireRegisteredType(type, '_emval_take_value');
      var v = type['readValueFromPointer'](argv);
      return __emval_register(v);
    }

  function _abort() {
      abort('native code called abort()');
    }

  function _emscripten_memcpy_big(dest, src, num) {
      HEAPU8.copyWithin(dest, src, src + num);
    }

  function abortOnCannotGrowMemory(requestedSize) {
      abort('Cannot enlarge memory arrays to size ' + requestedSize + ' bytes (OOM). Either (1) compile with  -s INITIAL_MEMORY=X  with X higher than the current value ' + HEAP8.length + ', (2) compile with  -s ALLOW_MEMORY_GROWTH=1  which allows increasing the size at runtime, or (3) if you want malloc to return NULL (0) instead of this abort, compile with  -s ABORTING_MALLOC=0 ');
    }
  function _emscripten_resize_heap(requestedSize) {
      var oldSize = HEAPU8.length;
      requestedSize = requestedSize >>> 0;
      abortOnCannotGrowMemory(requestedSize);
    }
embind_init_charCodes();
BindingError = Module['BindingError'] = extendError(Error, 'BindingError');;
InternalError = Module['InternalError'] = extendError(Error, 'InternalError');;
init_emval();;
UnboundTypeError = Module['UnboundTypeError'] = extendError(Error, 'UnboundTypeError');;
var ASSERTIONS = true;



/** @type {function(string, boolean=, number=)} */
function intArrayFromString(stringy, dontAddNull, length) {
  var len = length > 0 ? length : lengthBytesUTF8(stringy)+1;
  var u8array = new Array(len);
  var numBytesWritten = stringToUTF8Array(stringy, u8array, 0, u8array.length);
  if (dontAddNull) u8array.length = numBytesWritten;
  return u8array;
}

function intArrayToString(array) {
  var ret = [];
  for (var i = 0; i < array.length; i++) {
    var chr = array[i];
    if (chr > 0xFF) {
      if (ASSERTIONS) {
        assert(false, 'Character code ' + chr + ' (' + String.fromCharCode(chr) + ')  at offset ' + i + ' not in 0x00-0xFF.');
      }
      chr &= 0xFF;
    }
    ret.push(String.fromCharCode(chr));
  }
  return ret.join('');
}


// Copied from https://github.com/strophe/strophejs/blob/e06d027/src/polyfills.js#L149

// This code was written by Tyler Akins and has been placed in the
// public domain.  It would be nice if you left this header intact.
// Base64 code from Tyler Akins -- http://rumkin.com

/**
 * Decodes a base64 string.
 * @param {string} input The string to decode.
 */
var decodeBase64 = typeof atob === 'function' ? atob : function (input) {
  var keyStr = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=';

  var output = '';
  var chr1, chr2, chr3;
  var enc1, enc2, enc3, enc4;
  var i = 0;
  // remove all characters that are not A-Z, a-z, 0-9, +, /, or =
  input = input.replace(/[^A-Za-z0-9\+\/\=]/g, '');
  do {
    enc1 = keyStr.indexOf(input.charAt(i++));
    enc2 = keyStr.indexOf(input.charAt(i++));
    enc3 = keyStr.indexOf(input.charAt(i++));
    enc4 = keyStr.indexOf(input.charAt(i++));

    chr1 = (enc1 << 2) | (enc2 >> 4);
    chr2 = ((enc2 & 15) << 4) | (enc3 >> 2);
    chr3 = ((enc3 & 3) << 6) | enc4;

    output = output + String.fromCharCode(chr1);

    if (enc3 !== 64) {
      output = output + String.fromCharCode(chr2);
    }
    if (enc4 !== 64) {
      output = output + String.fromCharCode(chr3);
    }
  } while (i < input.length);
  return output;
};

// Converts a string of base64 into a byte array.
// Throws error on invalid input.
function intArrayFromBase64(s) {
  if (typeof ENVIRONMENT_IS_NODE === 'boolean' && ENVIRONMENT_IS_NODE) {
    var buf = Buffer.from(s, 'base64');
    return new Uint8Array(buf['buffer'], buf['byteOffset'], buf['byteLength']);
  }

  try {
    var decoded = decodeBase64(s);
    var bytes = new Uint8Array(decoded.length);
    for (var i = 0 ; i < decoded.length ; ++i) {
      bytes[i] = decoded.charCodeAt(i);
    }
    return bytes;
  } catch (_) {
    throw new Error('Converting base64 string to bytes failed.');
  }
}

// If filename is a base64 data URI, parses and returns data (Buffer on node,
// Uint8Array otherwise). If filename is not a base64 data URI, returns undefined.
function tryParseAsDataURI(filename) {
  if (!isDataURI(filename)) {
    return;
  }

  return intArrayFromBase64(filename.slice(dataURIPrefix.length));
}


var asmLibraryArg = {
  "__assert_fail": ___assert_fail,
  "__cxa_allocate_exception": ___cxa_allocate_exception,
  "__cxa_throw": ___cxa_throw,
  "_embind_register_bigint": __embind_register_bigint,
  "_embind_register_bool": __embind_register_bool,
  "_embind_register_emval": __embind_register_emval,
  "_embind_register_float": __embind_register_float,
  "_embind_register_function": __embind_register_function,
  "_embind_register_integer": __embind_register_integer,
  "_embind_register_memory_view": __embind_register_memory_view,
  "_embind_register_std_string": __embind_register_std_string,
  "_embind_register_std_wstring": __embind_register_std_wstring,
  "_embind_register_void": __embind_register_void,
  "_emval_as": __emval_as,
  "_emval_call_void_method": __emval_call_void_method,
  "_emval_decref": __emval_decref,
  "_emval_get_method_caller": __emval_get_method_caller,
  "_emval_get_property": __emval_get_property,
  "_emval_incref": __emval_incref,
  "_emval_new_array": __emval_new_array,
  "_emval_new_cstring": __emval_new_cstring,
  "_emval_new_object": __emval_new_object,
  "_emval_run_destructors": __emval_run_destructors,
  "_emval_set_property": __emval_set_property,
  "_emval_take_value": __emval_take_value,
  "abort": _abort,
  "emscripten_memcpy_big": _emscripten_memcpy_big,
  "emscripten_resize_heap": _emscripten_resize_heap
};
var asm = createWasm();
/** @type {function(...*):?} */
var ___wasm_call_ctors = Module["___wasm_call_ctors"] = createExportWrapper("__wasm_call_ctors");

/** @type {function(...*):?} */
var ___getTypeName = Module["___getTypeName"] = createExportWrapper("__getTypeName");

/** @type {function(...*):?} */
var ___embind_register_native_and_builtin_types = Module["___embind_register_native_and_builtin_types"] = createExportWrapper("__embind_register_native_and_builtin_types");

/** @type {function(...*):?} */
var _fflush = Module["_fflush"] = createExportWrapper("fflush");

/** @type {function(...*):?} */
var _malloc = Module["_malloc"] = createExportWrapper("malloc");

/** @type {function(...*):?} */
var ___errno_location = Module["___errno_location"] = createExportWrapper("__errno_location");

/** @type {function(...*):?} */
var stackSave = Module["stackSave"] = createExportWrapper("stackSave");

/** @type {function(...*):?} */
var stackRestore = Module["stackRestore"] = createExportWrapper("stackRestore");

/** @type {function(...*):?} */
var stackAlloc = Module["stackAlloc"] = createExportWrapper("stackAlloc");

/** @type {function(...*):?} */
var _emscripten_stack_init = Module["_emscripten_stack_init"] = function() {
  return (_emscripten_stack_init = Module["_emscripten_stack_init"] = Module["asm"]["emscripten_stack_init"]).apply(null, arguments);
};

/** @type {function(...*):?} */
var _emscripten_stack_get_free = Module["_emscripten_stack_get_free"] = function() {
  return (_emscripten_stack_get_free = Module["_emscripten_stack_get_free"] = Module["asm"]["emscripten_stack_get_free"]).apply(null, arguments);
};

/** @type {function(...*):?} */
var _emscripten_stack_get_end = Module["_emscripten_stack_get_end"] = function() {
  return (_emscripten_stack_get_end = Module["_emscripten_stack_get_end"] = Module["asm"]["emscripten_stack_get_end"]).apply(null, arguments);
};

/** @type {function(...*):?} */
var _free = Module["_free"] = createExportWrapper("free");





// === Auto-generated postamble setup entry stuff ===

if (!Object.getOwnPropertyDescriptor(Module, "intArrayFromString")) Module["intArrayFromString"] = function() { abort("'intArrayFromString' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "intArrayToString")) Module["intArrayToString"] = function() { abort("'intArrayToString' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "ccall")) Module["ccall"] = function() { abort("'ccall' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "cwrap")) Module["cwrap"] = function() { abort("'cwrap' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "setValue")) Module["setValue"] = function() { abort("'setValue' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getValue")) Module["getValue"] = function() { abort("'getValue' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "allocate")) Module["allocate"] = function() { abort("'allocate' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "UTF8ArrayToString")) Module["UTF8ArrayToString"] = function() { abort("'UTF8ArrayToString' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "UTF8ToString")) Module["UTF8ToString"] = function() { abort("'UTF8ToString' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "stringToUTF8Array")) Module["stringToUTF8Array"] = function() { abort("'stringToUTF8Array' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "stringToUTF8")) Module["stringToUTF8"] = function() { abort("'stringToUTF8' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "lengthBytesUTF8")) Module["lengthBytesUTF8"] = function() { abort("'lengthBytesUTF8' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "stackTrace")) Module["stackTrace"] = function() { abort("'stackTrace' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "addOnPreRun")) Module["addOnPreRun"] = function() { abort("'addOnPreRun' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "addOnInit")) Module["addOnInit"] = function() { abort("'addOnInit' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "addOnPreMain")) Module["addOnPreMain"] = function() { abort("'addOnPreMain' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "addOnExit")) Module["addOnExit"] = function() { abort("'addOnExit' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "addOnPostRun")) Module["addOnPostRun"] = function() { abort("'addOnPostRun' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "writeStringToMemory")) Module["writeStringToMemory"] = function() { abort("'writeStringToMemory' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "writeArrayToMemory")) Module["writeArrayToMemory"] = function() { abort("'writeArrayToMemory' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "writeAsciiToMemory")) Module["writeAsciiToMemory"] = function() { abort("'writeAsciiToMemory' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "addRunDependency")) Module["addRunDependency"] = function() { abort("'addRunDependency' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ). Alternatively, forcing filesystem support (-s FORCE_FILESYSTEM=1) can export this for you") };
if (!Object.getOwnPropertyDescriptor(Module, "removeRunDependency")) Module["removeRunDependency"] = function() { abort("'removeRunDependency' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ). Alternatively, forcing filesystem support (-s FORCE_FILESYSTEM=1) can export this for you") };
if (!Object.getOwnPropertyDescriptor(Module, "FS_createFolder")) Module["FS_createFolder"] = function() { abort("'FS_createFolder' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "FS_createPath")) Module["FS_createPath"] = function() { abort("'FS_createPath' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ). Alternatively, forcing filesystem support (-s FORCE_FILESYSTEM=1) can export this for you") };
if (!Object.getOwnPropertyDescriptor(Module, "FS_createDataFile")) Module["FS_createDataFile"] = function() { abort("'FS_createDataFile' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ). Alternatively, forcing filesystem support (-s FORCE_FILESYSTEM=1) can export this for you") };
if (!Object.getOwnPropertyDescriptor(Module, "FS_createPreloadedFile")) Module["FS_createPreloadedFile"] = function() { abort("'FS_createPreloadedFile' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ). Alternatively, forcing filesystem support (-s FORCE_FILESYSTEM=1) can export this for you") };
if (!Object.getOwnPropertyDescriptor(Module, "FS_createLazyFile")) Module["FS_createLazyFile"] = function() { abort("'FS_createLazyFile' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ). Alternatively, forcing filesystem support (-s FORCE_FILESYSTEM=1) can export this for you") };
if (!Object.getOwnPropertyDescriptor(Module, "FS_createLink")) Module["FS_createLink"] = function() { abort("'FS_createLink' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "FS_createDevice")) Module["FS_createDevice"] = function() { abort("'FS_createDevice' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ). Alternatively, forcing filesystem support (-s FORCE_FILESYSTEM=1) can export this for you") };
if (!Object.getOwnPropertyDescriptor(Module, "FS_unlink")) Module["FS_unlink"] = function() { abort("'FS_unlink' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ). Alternatively, forcing filesystem support (-s FORCE_FILESYSTEM=1) can export this for you") };
if (!Object.getOwnPropertyDescriptor(Module, "getLEB")) Module["getLEB"] = function() { abort("'getLEB' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getFunctionTables")) Module["getFunctionTables"] = function() { abort("'getFunctionTables' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "alignFunctionTables")) Module["alignFunctionTables"] = function() { abort("'alignFunctionTables' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registerFunctions")) Module["registerFunctions"] = function() { abort("'registerFunctions' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "addFunction")) Module["addFunction"] = function() { abort("'addFunction' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "removeFunction")) Module["removeFunction"] = function() { abort("'removeFunction' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getFuncWrapper")) Module["getFuncWrapper"] = function() { abort("'getFuncWrapper' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "prettyPrint")) Module["prettyPrint"] = function() { abort("'prettyPrint' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "dynCall")) Module["dynCall"] = function() { abort("'dynCall' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getCompilerSetting")) Module["getCompilerSetting"] = function() { abort("'getCompilerSetting' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "print")) Module["print"] = function() { abort("'print' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "printErr")) Module["printErr"] = function() { abort("'printErr' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getTempRet0")) Module["getTempRet0"] = function() { abort("'getTempRet0' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "setTempRet0")) Module["setTempRet0"] = function() { abort("'setTempRet0' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "callMain")) Module["callMain"] = function() { abort("'callMain' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "abort")) Module["abort"] = function() { abort("'abort' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "keepRuntimeAlive")) Module["keepRuntimeAlive"] = function() { abort("'keepRuntimeAlive' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "zeroMemory")) Module["zeroMemory"] = function() { abort("'zeroMemory' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "stringToNewUTF8")) Module["stringToNewUTF8"] = function() { abort("'stringToNewUTF8' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "setFileTime")) Module["setFileTime"] = function() { abort("'setFileTime' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "abortOnCannotGrowMemory")) Module["abortOnCannotGrowMemory"] = function() { abort("'abortOnCannotGrowMemory' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "emscripten_realloc_buffer")) Module["emscripten_realloc_buffer"] = function() { abort("'emscripten_realloc_buffer' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "ENV")) Module["ENV"] = function() { abort("'ENV' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "ERRNO_CODES")) Module["ERRNO_CODES"] = function() { abort("'ERRNO_CODES' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "ERRNO_MESSAGES")) Module["ERRNO_MESSAGES"] = function() { abort("'ERRNO_MESSAGES' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "setErrNo")) Module["setErrNo"] = function() { abort("'setErrNo' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "inetPton4")) Module["inetPton4"] = function() { abort("'inetPton4' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "inetNtop4")) Module["inetNtop4"] = function() { abort("'inetNtop4' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "inetPton6")) Module["inetPton6"] = function() { abort("'inetPton6' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "inetNtop6")) Module["inetNtop6"] = function() { abort("'inetNtop6' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "readSockaddr")) Module["readSockaddr"] = function() { abort("'readSockaddr' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "writeSockaddr")) Module["writeSockaddr"] = function() { abort("'writeSockaddr' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "DNS")) Module["DNS"] = function() { abort("'DNS' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getHostByName")) Module["getHostByName"] = function() { abort("'getHostByName' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "GAI_ERRNO_MESSAGES")) Module["GAI_ERRNO_MESSAGES"] = function() { abort("'GAI_ERRNO_MESSAGES' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "Protocols")) Module["Protocols"] = function() { abort("'Protocols' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "Sockets")) Module["Sockets"] = function() { abort("'Sockets' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getRandomDevice")) Module["getRandomDevice"] = function() { abort("'getRandomDevice' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "traverseStack")) Module["traverseStack"] = function() { abort("'traverseStack' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "UNWIND_CACHE")) Module["UNWIND_CACHE"] = function() { abort("'UNWIND_CACHE' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "readAsmConstArgsArray")) Module["readAsmConstArgsArray"] = function() { abort("'readAsmConstArgsArray' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "readAsmConstArgs")) Module["readAsmConstArgs"] = function() { abort("'readAsmConstArgs' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "mainThreadEM_ASM")) Module["mainThreadEM_ASM"] = function() { abort("'mainThreadEM_ASM' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "jstoi_q")) Module["jstoi_q"] = function() { abort("'jstoi_q' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "jstoi_s")) Module["jstoi_s"] = function() { abort("'jstoi_s' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getExecutableName")) Module["getExecutableName"] = function() { abort("'getExecutableName' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "listenOnce")) Module["listenOnce"] = function() { abort("'listenOnce' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "autoResumeAudioContext")) Module["autoResumeAudioContext"] = function() { abort("'autoResumeAudioContext' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "dynCallLegacy")) Module["dynCallLegacy"] = function() { abort("'dynCallLegacy' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getDynCaller")) Module["getDynCaller"] = function() { abort("'getDynCaller' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "dynCall")) Module["dynCall"] = function() { abort("'dynCall' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "callRuntimeCallbacks")) Module["callRuntimeCallbacks"] = function() { abort("'callRuntimeCallbacks' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "handleException")) Module["handleException"] = function() { abort("'handleException' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "runtimeKeepalivePush")) Module["runtimeKeepalivePush"] = function() { abort("'runtimeKeepalivePush' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "runtimeKeepalivePop")) Module["runtimeKeepalivePop"] = function() { abort("'runtimeKeepalivePop' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "callUserCallback")) Module["callUserCallback"] = function() { abort("'callUserCallback' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "maybeExit")) Module["maybeExit"] = function() { abort("'maybeExit' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "safeSetTimeout")) Module["safeSetTimeout"] = function() { abort("'safeSetTimeout' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "asmjsMangle")) Module["asmjsMangle"] = function() { abort("'asmjsMangle' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "asyncLoad")) Module["asyncLoad"] = function() { abort("'asyncLoad' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "alignMemory")) Module["alignMemory"] = function() { abort("'alignMemory' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "mmapAlloc")) Module["mmapAlloc"] = function() { abort("'mmapAlloc' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "reallyNegative")) Module["reallyNegative"] = function() { abort("'reallyNegative' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "unSign")) Module["unSign"] = function() { abort("'unSign' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "reSign")) Module["reSign"] = function() { abort("'reSign' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "formatString")) Module["formatString"] = function() { abort("'formatString' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "PATH")) Module["PATH"] = function() { abort("'PATH' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "PATH_FS")) Module["PATH_FS"] = function() { abort("'PATH_FS' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "SYSCALLS")) Module["SYSCALLS"] = function() { abort("'SYSCALLS' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "syscallMmap2")) Module["syscallMmap2"] = function() { abort("'syscallMmap2' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "syscallMunmap")) Module["syscallMunmap"] = function() { abort("'syscallMunmap' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getSocketFromFD")) Module["getSocketFromFD"] = function() { abort("'getSocketFromFD' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getSocketAddress")) Module["getSocketAddress"] = function() { abort("'getSocketAddress' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "JSEvents")) Module["JSEvents"] = function() { abort("'JSEvents' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registerKeyEventCallback")) Module["registerKeyEventCallback"] = function() { abort("'registerKeyEventCallback' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "specialHTMLTargets")) Module["specialHTMLTargets"] = function() { abort("'specialHTMLTargets' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "maybeCStringToJsString")) Module["maybeCStringToJsString"] = function() { abort("'maybeCStringToJsString' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "findEventTarget")) Module["findEventTarget"] = function() { abort("'findEventTarget' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "findCanvasEventTarget")) Module["findCanvasEventTarget"] = function() { abort("'findCanvasEventTarget' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getBoundingClientRect")) Module["getBoundingClientRect"] = function() { abort("'getBoundingClientRect' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "fillMouseEventData")) Module["fillMouseEventData"] = function() { abort("'fillMouseEventData' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registerMouseEventCallback")) Module["registerMouseEventCallback"] = function() { abort("'registerMouseEventCallback' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registerWheelEventCallback")) Module["registerWheelEventCallback"] = function() { abort("'registerWheelEventCallback' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registerUiEventCallback")) Module["registerUiEventCallback"] = function() { abort("'registerUiEventCallback' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registerFocusEventCallback")) Module["registerFocusEventCallback"] = function() { abort("'registerFocusEventCallback' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "fillDeviceOrientationEventData")) Module["fillDeviceOrientationEventData"] = function() { abort("'fillDeviceOrientationEventData' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registerDeviceOrientationEventCallback")) Module["registerDeviceOrientationEventCallback"] = function() { abort("'registerDeviceOrientationEventCallback' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "fillDeviceMotionEventData")) Module["fillDeviceMotionEventData"] = function() { abort("'fillDeviceMotionEventData' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registerDeviceMotionEventCallback")) Module["registerDeviceMotionEventCallback"] = function() { abort("'registerDeviceMotionEventCallback' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "screenOrientation")) Module["screenOrientation"] = function() { abort("'screenOrientation' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "fillOrientationChangeEventData")) Module["fillOrientationChangeEventData"] = function() { abort("'fillOrientationChangeEventData' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registerOrientationChangeEventCallback")) Module["registerOrientationChangeEventCallback"] = function() { abort("'registerOrientationChangeEventCallback' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "fillFullscreenChangeEventData")) Module["fillFullscreenChangeEventData"] = function() { abort("'fillFullscreenChangeEventData' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registerFullscreenChangeEventCallback")) Module["registerFullscreenChangeEventCallback"] = function() { abort("'registerFullscreenChangeEventCallback' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registerRestoreOldStyle")) Module["registerRestoreOldStyle"] = function() { abort("'registerRestoreOldStyle' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "hideEverythingExceptGivenElement")) Module["hideEverythingExceptGivenElement"] = function() { abort("'hideEverythingExceptGivenElement' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "restoreHiddenElements")) Module["restoreHiddenElements"] = function() { abort("'restoreHiddenElements' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "setLetterbox")) Module["setLetterbox"] = function() { abort("'setLetterbox' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "currentFullscreenStrategy")) Module["currentFullscreenStrategy"] = function() { abort("'currentFullscreenStrategy' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "restoreOldWindowedStyle")) Module["restoreOldWindowedStyle"] = function() { abort("'restoreOldWindowedStyle' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "softFullscreenResizeWebGLRenderTarget")) Module["softFullscreenResizeWebGLRenderTarget"] = function() { abort("'softFullscreenResizeWebGLRenderTarget' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "doRequestFullscreen")) Module["doRequestFullscreen"] = function() { abort("'doRequestFullscreen' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "fillPointerlockChangeEventData")) Module["fillPointerlockChangeEventData"] = function() { abort("'fillPointerlockChangeEventData' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registerPointerlockChangeEventCallback")) Module["registerPointerlockChangeEventCallback"] = function() { abort("'registerPointerlockChangeEventCallback' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registerPointerlockErrorEventCallback")) Module["registerPointerlockErrorEventCallback"] = function() { abort("'registerPointerlockErrorEventCallback' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "requestPointerLock")) Module["requestPointerLock"] = function() { abort("'requestPointerLock' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "fillVisibilityChangeEventData")) Module["fillVisibilityChangeEventData"] = function() { abort("'fillVisibilityChangeEventData' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registerVisibilityChangeEventCallback")) Module["registerVisibilityChangeEventCallback"] = function() { abort("'registerVisibilityChangeEventCallback' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registerTouchEventCallback")) Module["registerTouchEventCallback"] = function() { abort("'registerTouchEventCallback' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "fillGamepadEventData")) Module["fillGamepadEventData"] = function() { abort("'fillGamepadEventData' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registerGamepadEventCallback")) Module["registerGamepadEventCallback"] = function() { abort("'registerGamepadEventCallback' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registerBeforeUnloadEventCallback")) Module["registerBeforeUnloadEventCallback"] = function() { abort("'registerBeforeUnloadEventCallback' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "fillBatteryEventData")) Module["fillBatteryEventData"] = function() { abort("'fillBatteryEventData' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "battery")) Module["battery"] = function() { abort("'battery' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registerBatteryEventCallback")) Module["registerBatteryEventCallback"] = function() { abort("'registerBatteryEventCallback' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "setCanvasElementSize")) Module["setCanvasElementSize"] = function() { abort("'setCanvasElementSize' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getCanvasElementSize")) Module["getCanvasElementSize"] = function() { abort("'getCanvasElementSize' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "setImmediateWrapped")) Module["setImmediateWrapped"] = function() { abort("'setImmediateWrapped' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "clearImmediateWrapped")) Module["clearImmediateWrapped"] = function() { abort("'clearImmediateWrapped' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "polyfillSetImmediate")) Module["polyfillSetImmediate"] = function() { abort("'polyfillSetImmediate' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "demangle")) Module["demangle"] = function() { abort("'demangle' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "demangleAll")) Module["demangleAll"] = function() { abort("'demangleAll' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "jsStackTrace")) Module["jsStackTrace"] = function() { abort("'jsStackTrace' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "stackTrace")) Module["stackTrace"] = function() { abort("'stackTrace' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getEnvStrings")) Module["getEnvStrings"] = function() { abort("'getEnvStrings' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "checkWasiClock")) Module["checkWasiClock"] = function() { abort("'checkWasiClock' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "flush_NO_FILESYSTEM")) Module["flush_NO_FILESYSTEM"] = function() { abort("'flush_NO_FILESYSTEM' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "writeI53ToI64")) Module["writeI53ToI64"] = function() { abort("'writeI53ToI64' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "writeI53ToI64Clamped")) Module["writeI53ToI64Clamped"] = function() { abort("'writeI53ToI64Clamped' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "writeI53ToI64Signaling")) Module["writeI53ToI64Signaling"] = function() { abort("'writeI53ToI64Signaling' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "writeI53ToU64Clamped")) Module["writeI53ToU64Clamped"] = function() { abort("'writeI53ToU64Clamped' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "writeI53ToU64Signaling")) Module["writeI53ToU64Signaling"] = function() { abort("'writeI53ToU64Signaling' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "readI53FromI64")) Module["readI53FromI64"] = function() { abort("'readI53FromI64' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "readI53FromU64")) Module["readI53FromU64"] = function() { abort("'readI53FromU64' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "convertI32PairToI53")) Module["convertI32PairToI53"] = function() { abort("'convertI32PairToI53' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "convertU32PairToI53")) Module["convertU32PairToI53"] = function() { abort("'convertU32PairToI53' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "uncaughtExceptionCount")) Module["uncaughtExceptionCount"] = function() { abort("'uncaughtExceptionCount' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "exceptionLast")) Module["exceptionLast"] = function() { abort("'exceptionLast' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "exceptionCaught")) Module["exceptionCaught"] = function() { abort("'exceptionCaught' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "ExceptionInfo")) Module["ExceptionInfo"] = function() { abort("'ExceptionInfo' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "CatchInfo")) Module["CatchInfo"] = function() { abort("'CatchInfo' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "exception_addRef")) Module["exception_addRef"] = function() { abort("'exception_addRef' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "exception_decRef")) Module["exception_decRef"] = function() { abort("'exception_decRef' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "Browser")) Module["Browser"] = function() { abort("'Browser' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "funcWrappers")) Module["funcWrappers"] = function() { abort("'funcWrappers' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getFuncWrapper")) Module["getFuncWrapper"] = function() { abort("'getFuncWrapper' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "setMainLoop")) Module["setMainLoop"] = function() { abort("'setMainLoop' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "wget")) Module["wget"] = function() { abort("'wget' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "FS")) Module["FS"] = function() { abort("'FS' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "MEMFS")) Module["MEMFS"] = function() { abort("'MEMFS' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "TTY")) Module["TTY"] = function() { abort("'TTY' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "PIPEFS")) Module["PIPEFS"] = function() { abort("'PIPEFS' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "SOCKFS")) Module["SOCKFS"] = function() { abort("'SOCKFS' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "_setNetworkCallback")) Module["_setNetworkCallback"] = function() { abort("'_setNetworkCallback' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "tempFixedLengthArray")) Module["tempFixedLengthArray"] = function() { abort("'tempFixedLengthArray' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "miniTempWebGLFloatBuffers")) Module["miniTempWebGLFloatBuffers"] = function() { abort("'miniTempWebGLFloatBuffers' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "heapObjectForWebGLType")) Module["heapObjectForWebGLType"] = function() { abort("'heapObjectForWebGLType' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "heapAccessShiftForWebGLHeap")) Module["heapAccessShiftForWebGLHeap"] = function() { abort("'heapAccessShiftForWebGLHeap' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "GL")) Module["GL"] = function() { abort("'GL' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "emscriptenWebGLGet")) Module["emscriptenWebGLGet"] = function() { abort("'emscriptenWebGLGet' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "computeUnpackAlignedImageSize")) Module["computeUnpackAlignedImageSize"] = function() { abort("'computeUnpackAlignedImageSize' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "emscriptenWebGLGetTexPixelData")) Module["emscriptenWebGLGetTexPixelData"] = function() { abort("'emscriptenWebGLGetTexPixelData' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "emscriptenWebGLGetUniform")) Module["emscriptenWebGLGetUniform"] = function() { abort("'emscriptenWebGLGetUniform' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "webglGetUniformLocation")) Module["webglGetUniformLocation"] = function() { abort("'webglGetUniformLocation' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "webglPrepareUniformLocationsBeforeFirstUse")) Module["webglPrepareUniformLocationsBeforeFirstUse"] = function() { abort("'webglPrepareUniformLocationsBeforeFirstUse' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "webglGetLeftBracePos")) Module["webglGetLeftBracePos"] = function() { abort("'webglGetLeftBracePos' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "emscriptenWebGLGetVertexAttrib")) Module["emscriptenWebGLGetVertexAttrib"] = function() { abort("'emscriptenWebGLGetVertexAttrib' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "writeGLArray")) Module["writeGLArray"] = function() { abort("'writeGLArray' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "AL")) Module["AL"] = function() { abort("'AL' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "SDL_unicode")) Module["SDL_unicode"] = function() { abort("'SDL_unicode' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "SDL_ttfContext")) Module["SDL_ttfContext"] = function() { abort("'SDL_ttfContext' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "SDL_audio")) Module["SDL_audio"] = function() { abort("'SDL_audio' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "SDL")) Module["SDL"] = function() { abort("'SDL' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "SDL_gfx")) Module["SDL_gfx"] = function() { abort("'SDL_gfx' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "GLUT")) Module["GLUT"] = function() { abort("'GLUT' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "EGL")) Module["EGL"] = function() { abort("'EGL' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "GLFW_Window")) Module["GLFW_Window"] = function() { abort("'GLFW_Window' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "GLFW")) Module["GLFW"] = function() { abort("'GLFW' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "GLEW")) Module["GLEW"] = function() { abort("'GLEW' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "IDBStore")) Module["IDBStore"] = function() { abort("'IDBStore' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "runAndAbortIfError")) Module["runAndAbortIfError"] = function() { abort("'runAndAbortIfError' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "emval_handle_array")) Module["emval_handle_array"] = function() { abort("'emval_handle_array' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "emval_free_list")) Module["emval_free_list"] = function() { abort("'emval_free_list' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "emval_symbols")) Module["emval_symbols"] = function() { abort("'emval_symbols' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "init_emval")) Module["init_emval"] = function() { abort("'init_emval' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "count_emval_handles")) Module["count_emval_handles"] = function() { abort("'count_emval_handles' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "get_first_emval")) Module["get_first_emval"] = function() { abort("'get_first_emval' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getStringOrSymbol")) Module["getStringOrSymbol"] = function() { abort("'getStringOrSymbol' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "requireHandle")) Module["requireHandle"] = function() { abort("'requireHandle' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "emval_newers")) Module["emval_newers"] = function() { abort("'emval_newers' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "craftEmvalAllocator")) Module["craftEmvalAllocator"] = function() { abort("'craftEmvalAllocator' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "emval_get_global")) Module["emval_get_global"] = function() { abort("'emval_get_global' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "emval_methodCallers")) Module["emval_methodCallers"] = function() { abort("'emval_methodCallers' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "InternalError")) Module["InternalError"] = function() { abort("'InternalError' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "BindingError")) Module["BindingError"] = function() { abort("'BindingError' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "UnboundTypeError")) Module["UnboundTypeError"] = function() { abort("'UnboundTypeError' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "PureVirtualError")) Module["PureVirtualError"] = function() { abort("'PureVirtualError' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "init_embind")) Module["init_embind"] = function() { abort("'init_embind' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "throwInternalError")) Module["throwInternalError"] = function() { abort("'throwInternalError' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "throwBindingError")) Module["throwBindingError"] = function() { abort("'throwBindingError' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "throwUnboundTypeError")) Module["throwUnboundTypeError"] = function() { abort("'throwUnboundTypeError' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "ensureOverloadTable")) Module["ensureOverloadTable"] = function() { abort("'ensureOverloadTable' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "exposePublicSymbol")) Module["exposePublicSymbol"] = function() { abort("'exposePublicSymbol' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "replacePublicSymbol")) Module["replacePublicSymbol"] = function() { abort("'replacePublicSymbol' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "extendError")) Module["extendError"] = function() { abort("'extendError' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "createNamedFunction")) Module["createNamedFunction"] = function() { abort("'createNamedFunction' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registeredInstances")) Module["registeredInstances"] = function() { abort("'registeredInstances' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getBasestPointer")) Module["getBasestPointer"] = function() { abort("'getBasestPointer' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registerInheritedInstance")) Module["registerInheritedInstance"] = function() { abort("'registerInheritedInstance' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "unregisterInheritedInstance")) Module["unregisterInheritedInstance"] = function() { abort("'unregisterInheritedInstance' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getInheritedInstance")) Module["getInheritedInstance"] = function() { abort("'getInheritedInstance' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getInheritedInstanceCount")) Module["getInheritedInstanceCount"] = function() { abort("'getInheritedInstanceCount' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getLiveInheritedInstances")) Module["getLiveInheritedInstances"] = function() { abort("'getLiveInheritedInstances' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registeredTypes")) Module["registeredTypes"] = function() { abort("'registeredTypes' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "awaitingDependencies")) Module["awaitingDependencies"] = function() { abort("'awaitingDependencies' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "typeDependencies")) Module["typeDependencies"] = function() { abort("'typeDependencies' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registeredPointers")) Module["registeredPointers"] = function() { abort("'registeredPointers' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "registerType")) Module["registerType"] = function() { abort("'registerType' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "whenDependentTypesAreResolved")) Module["whenDependentTypesAreResolved"] = function() { abort("'whenDependentTypesAreResolved' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "embind_charCodes")) Module["embind_charCodes"] = function() { abort("'embind_charCodes' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "embind_init_charCodes")) Module["embind_init_charCodes"] = function() { abort("'embind_init_charCodes' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "readLatin1String")) Module["readLatin1String"] = function() { abort("'readLatin1String' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getTypeName")) Module["getTypeName"] = function() { abort("'getTypeName' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "heap32VectorToArray")) Module["heap32VectorToArray"] = function() { abort("'heap32VectorToArray' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "requireRegisteredType")) Module["requireRegisteredType"] = function() { abort("'requireRegisteredType' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "getShiftFromSize")) Module["getShiftFromSize"] = function() { abort("'getShiftFromSize' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "integerReadValueFromPointer")) Module["integerReadValueFromPointer"] = function() { abort("'integerReadValueFromPointer' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "enumReadValueFromPointer")) Module["enumReadValueFromPointer"] = function() { abort("'enumReadValueFromPointer' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "floatReadValueFromPointer")) Module["floatReadValueFromPointer"] = function() { abort("'floatReadValueFromPointer' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "simpleReadValueFromPointer")) Module["simpleReadValueFromPointer"] = function() { abort("'simpleReadValueFromPointer' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "runDestructors")) Module["runDestructors"] = function() { abort("'runDestructors' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "new_")) Module["new_"] = function() { abort("'new_' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "craftInvokerFunction")) Module["craftInvokerFunction"] = function() { abort("'craftInvokerFunction' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "embind__requireFunction")) Module["embind__requireFunction"] = function() { abort("'embind__requireFunction' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "tupleRegistrations")) Module["tupleRegistrations"] = function() { abort("'tupleRegistrations' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "structRegistrations")) Module["structRegistrations"] = function() { abort("'structRegistrations' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "genericPointerToWireType")) Module["genericPointerToWireType"] = function() { abort("'genericPointerToWireType' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "constNoSmartPtrRawPointerToWireType")) Module["constNoSmartPtrRawPointerToWireType"] = function() { abort("'constNoSmartPtrRawPointerToWireType' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "nonConstNoSmartPtrRawPointerToWireType")) Module["nonConstNoSmartPtrRawPointerToWireType"] = function() { abort("'nonConstNoSmartPtrRawPointerToWireType' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "init_RegisteredPointer")) Module["init_RegisteredPointer"] = function() { abort("'init_RegisteredPointer' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "RegisteredPointer")) Module["RegisteredPointer"] = function() { abort("'RegisteredPointer' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "RegisteredPointer_getPointee")) Module["RegisteredPointer_getPointee"] = function() { abort("'RegisteredPointer_getPointee' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "RegisteredPointer_destructor")) Module["RegisteredPointer_destructor"] = function() { abort("'RegisteredPointer_destructor' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "RegisteredPointer_deleteObject")) Module["RegisteredPointer_deleteObject"] = function() { abort("'RegisteredPointer_deleteObject' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "RegisteredPointer_fromWireType")) Module["RegisteredPointer_fromWireType"] = function() { abort("'RegisteredPointer_fromWireType' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "runDestructor")) Module["runDestructor"] = function() { abort("'runDestructor' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "releaseClassHandle")) Module["releaseClassHandle"] = function() { abort("'releaseClassHandle' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "finalizationGroup")) Module["finalizationGroup"] = function() { abort("'finalizationGroup' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "detachFinalizer_deps")) Module["detachFinalizer_deps"] = function() { abort("'detachFinalizer_deps' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "detachFinalizer")) Module["detachFinalizer"] = function() { abort("'detachFinalizer' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "attachFinalizer")) Module["attachFinalizer"] = function() { abort("'attachFinalizer' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "makeClassHandle")) Module["makeClassHandle"] = function() { abort("'makeClassHandle' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "init_ClassHandle")) Module["init_ClassHandle"] = function() { abort("'init_ClassHandle' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "ClassHandle")) Module["ClassHandle"] = function() { abort("'ClassHandle' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "ClassHandle_isAliasOf")) Module["ClassHandle_isAliasOf"] = function() { abort("'ClassHandle_isAliasOf' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "throwInstanceAlreadyDeleted")) Module["throwInstanceAlreadyDeleted"] = function() { abort("'throwInstanceAlreadyDeleted' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "ClassHandle_clone")) Module["ClassHandle_clone"] = function() { abort("'ClassHandle_clone' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "ClassHandle_delete")) Module["ClassHandle_delete"] = function() { abort("'ClassHandle_delete' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "deletionQueue")) Module["deletionQueue"] = function() { abort("'deletionQueue' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "ClassHandle_isDeleted")) Module["ClassHandle_isDeleted"] = function() { abort("'ClassHandle_isDeleted' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "ClassHandle_deleteLater")) Module["ClassHandle_deleteLater"] = function() { abort("'ClassHandle_deleteLater' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "flushPendingDeletes")) Module["flushPendingDeletes"] = function() { abort("'flushPendingDeletes' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "delayFunction")) Module["delayFunction"] = function() { abort("'delayFunction' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "setDelayFunction")) Module["setDelayFunction"] = function() { abort("'setDelayFunction' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "RegisteredClass")) Module["RegisteredClass"] = function() { abort("'RegisteredClass' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "shallowCopyInternalPointer")) Module["shallowCopyInternalPointer"] = function() { abort("'shallowCopyInternalPointer' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "downcastPointer")) Module["downcastPointer"] = function() { abort("'downcastPointer' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "upcastPointer")) Module["upcastPointer"] = function() { abort("'upcastPointer' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "validateThis")) Module["validateThis"] = function() { abort("'validateThis' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "char_0")) Module["char_0"] = function() { abort("'char_0' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "char_9")) Module["char_9"] = function() { abort("'char_9' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "makeLegalFunctionName")) Module["makeLegalFunctionName"] = function() { abort("'makeLegalFunctionName' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "warnOnce")) Module["warnOnce"] = function() { abort("'warnOnce' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "stackSave")) Module["stackSave"] = function() { abort("'stackSave' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "stackRestore")) Module["stackRestore"] = function() { abort("'stackRestore' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "stackAlloc")) Module["stackAlloc"] = function() { abort("'stackAlloc' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "AsciiToString")) Module["AsciiToString"] = function() { abort("'AsciiToString' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "stringToAscii")) Module["stringToAscii"] = function() { abort("'stringToAscii' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "UTF16ToString")) Module["UTF16ToString"] = function() { abort("'UTF16ToString' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "stringToUTF16")) Module["stringToUTF16"] = function() { abort("'stringToUTF16' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "lengthBytesUTF16")) Module["lengthBytesUTF16"] = function() { abort("'lengthBytesUTF16' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "UTF32ToString")) Module["UTF32ToString"] = function() { abort("'UTF32ToString' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "stringToUTF32")) Module["stringToUTF32"] = function() { abort("'stringToUTF32' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "lengthBytesUTF32")) Module["lengthBytesUTF32"] = function() { abort("'lengthBytesUTF32' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "allocateUTF8")) Module["allocateUTF8"] = function() { abort("'allocateUTF8' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "allocateUTF8OnStack")) Module["allocateUTF8OnStack"] = function() { abort("'allocateUTF8OnStack' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
Module["writeStackCookie"] = writeStackCookie;
Module["checkStackCookie"] = checkStackCookie;
if (!Object.getOwnPropertyDescriptor(Module, "intArrayFromBase64")) Module["intArrayFromBase64"] = function() { abort("'intArrayFromBase64' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "tryParseAsDataURI")) Module["tryParseAsDataURI"] = function() { abort("'tryParseAsDataURI' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") };
if (!Object.getOwnPropertyDescriptor(Module, "ALLOC_NORMAL")) Object.defineProperty(Module, "ALLOC_NORMAL", { configurable: true, get: function() { abort("'ALLOC_NORMAL' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") } });
if (!Object.getOwnPropertyDescriptor(Module, "ALLOC_STACK")) Object.defineProperty(Module, "ALLOC_STACK", { configurable: true, get: function() { abort("'ALLOC_STACK' was not exported. add it to EXPORTED_RUNTIME_METHODS (see the FAQ)") } });

var calledRun;

/**
 * @constructor
 * @this {ExitStatus}
 */
function ExitStatus(status) {
  this.name = "ExitStatus";
  this.message = "Program terminated with exit(" + status + ")";
  this.status = status;
}

var calledMain = false;

dependenciesFulfilled = function runCaller() {
  // If run has never been called, and we should call run (INVOKE_RUN is true, and Module.noInitialRun is not false)
  if (!calledRun) run();
  if (!calledRun) dependenciesFulfilled = runCaller; // try this again later, after new deps are fulfilled
};

function stackCheckInit() {
  // This is normally called automatically during __wasm_call_ctors but need to
  // get these values before even running any of the ctors so we call it redundantly
  // here.
  // TODO(sbc): Move writeStackCookie to native to to avoid this.
  _emscripten_stack_init();
  writeStackCookie();
}

/** @type {function(Array=)} */
function run(args) {
  args = args || arguments_;

  if (runDependencies > 0) {
    return;
  }

  stackCheckInit();

  preRun();

  // a preRun added a dependency, run will be called later
  if (runDependencies > 0) {
    return;
  }

  function doRun() {
    // run may have just been called through dependencies being fulfilled just in this very frame,
    // or while the async setStatus time below was happening
    if (calledRun) return;
    calledRun = true;
    Module['calledRun'] = true;

    if (ABORT) return;

    initRuntime();

    if (Module['onRuntimeInitialized']) Module['onRuntimeInitialized']();

    assert(!Module['_main'], 'compiled without a main, but one is present. if you added it from JS, use Module["onRuntimeInitialized"]');

    postRun();
  }

  if (Module['setStatus']) {
    Module['setStatus']('Running...');
    setTimeout(function() {
      setTimeout(function() {
        Module['setStatus']('');
      }, 1);
      doRun();
    }, 1);
  } else
  {
    doRun();
  }
  checkStackCookie();
}
Module['run'] = run;

function checkUnflushedContent() {
  // Compiler settings do not allow exiting the runtime, so flushing
  // the streams is not possible. but in ASSERTIONS mode we check
  // if there was something to flush, and if so tell the user they
  // should request that the runtime be exitable.
  // Normally we would not even include flush() at all, but in ASSERTIONS
  // builds we do so just for this check, and here we see if there is any
  // content to flush, that is, we check if there would have been
  // something a non-ASSERTIONS build would have not seen.
  // How we flush the streams depends on whether we are in SYSCALLS_REQUIRE_FILESYSTEM=0
  // mode (which has its own special function for this; otherwise, all
  // the code is inside libc)
  var oldOut = out;
  var oldErr = err;
  var has = false;
  out = err = function(x) {
    has = true;
  }
  try { // it doesn't matter if it fails
    var flush = null;
    if (flush) flush();
  } catch(e) {}
  out = oldOut;
  err = oldErr;
  if (has) {
    warnOnce('stdio streams had content in them that was not flushed. you should set EXIT_RUNTIME to 1 (see the FAQ), or make sure to emit a newline when you printf etc.');
    warnOnce('(this may also be due to not including full filesystem support - try building with -s FORCE_FILESYSTEM=1)');
  }
}

/** @param {boolean|number=} implicit */
function exit(status, implicit) {
  EXITSTATUS = status;

  checkUnflushedContent();

  if (keepRuntimeAlive()) {
    // if exit() was called, we may warn the user if the runtime isn't actually being shut down
    if (!implicit) {
      var msg = 'program exited (with status: ' + status + '), but EXIT_RUNTIME is not set, so halting execution but not exiting the runtime or preventing further async execution (build with EXIT_RUNTIME=1, if you want a true shutdown)';
      err(msg);
    }
  } else {
    exitRuntime();
  }

  procExit(status);
}

function procExit(code) {
  EXITSTATUS = code;
  if (!keepRuntimeAlive()) {
    if (Module['onExit']) Module['onExit'](code);
    ABORT = true;
  }
  quit_(code, new ExitStatus(code));
}

if (Module['preInit']) {
  if (typeof Module['preInit'] == 'function') Module['preInit'] = [Module['preInit']];
  while (Module['preInit'].length > 0) {
    Module['preInit'].pop()();
  }
}

run();





