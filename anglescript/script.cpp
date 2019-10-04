#include "script.h"
#include <iostream>

Script::Script()
    : scriptEngine_(nullptr),
      immediateContext_(nullptr),
      scriptNestingLevel_(0),
      executeConsoleCommands_(false) {
  scriptEngine_ = asCreateScriptEngine(ANGELSCRIPT_VERSION);
  if (!scriptEngine_) {
    std::cout << "Failed to create AngelScript engine." << std::endl;
    return;
  }

  scriptEngine_->SetUserData(this);
  scriptEngine_->SetEngineProperty(asEP_USE_CHARACTER_LITERALS, (asPWORD) true);
  scriptEngine_->SetEngineProperty(asEP_ALLOW_UNSAFE_REFERENCES,
                                   (asPWORD) true);
  scriptEngine_->SetEngineProperty(asEP_ALLOW_IMPLICIT_HANDLE_TYPES,
                                   (asPWORD) true);
  scriptEngine_->SetEngineProperty(asEP_BUILD_WITHOUT_LINE_CUES,
                                   (asPWORD) true);
  // The script compiler will write any compiler messages to the callback.
  scriptEngine_->SetMessageCallback(asMETHOD(Script, MessageCallback), this,
                                    asCALL_THISCALL);

  // configure engine:
  // Configure the script engine with all the functions,
  // and variables that the script should be able to use.
  // Register the script string type
  // Look at the implementation for this function for more information
  // on how to register a custom string type, and other object types.
  RegisterStdString(scriptEngine_);
  RegisterScriptArray(scriptEngine_, true);

  if (!strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY")) {
    // Register the functions that the scripts will be allowed to use.
    // Note how the return code is validated with an assert(). This helps
    // us discover where a problem occurs, and doesn't pollute the code
    // with a lot of if's. If an error occurs in release mode it will
    // be caught when a script is being built, so it is not necessary
    // to do the verification here as well.
    // r = engine->RegisterGlobalFunction("void Print(string &in)",
    // asFUNCTION(PrintString), asCALL_CDECL); assert( r >= 0 ); r =
    // engine->RegisterGlobalFunction("uint GetSystemTime()",
    // asFUNCTION(timeGetTime), asCALL_STDCALL); assert( r >= 0 );
  } else {
    // Notice how the registration is almost identical to the above.
    // r = engine->RegisterGlobalFunction("void Print(string &in)",
    // asFUNCTION(PrintString_Generic), asCALL_GENERIC); assert( r >= 0 );
    // r = engine->RegisterGlobalFunction("uint GetSystemTime()",
    // asFUNCTION(timeGetTime_Generic), asCALL_GENERIC); assert( r >= 0 );
  }

  // It is possible to register the functions, properties, and types in
  // configuration groups as well. When compiling the scripts it then
  // be defined which configuration groups should be available for that
  // script. If necessary a configuration group can also be removed from
  // the engine, so that the engine configuration could be changed
  // without having to recompile all the scripts.

  // Create the context for immediate execution
  immediateContext_ = scriptEngine_->CreateContext();

  immediateContext_->SetExceptionCallback(asMETHOD(Script, ExceptionCallback),
                                          this, asCALL_THISCALL);
  /*    // Register Script library object factories
      RegisterScriptLibrary(context_);
      // Register the Array, String & Dictionary API
      RegisterArray(scriptEngine_);
      RegisterString(scriptEngine_);
      RegisterDictionary(scriptEngine_);
      RegisterScriptInterfaceAPI(scriptEngine_);

      // Register the rest of the script API
      RegisterMathAPI(scriptEngine_);
      RegisterCoreAPI(scriptEngine_);
      RegisterIOAPI(scriptEngine_);
      RegisterResourceAPI(scriptEngine_);
      RegisterSceneAPI(scriptEngine_);
      RegisterGraphicsAPI(scriptEngine_);
      RegisterInputAPI(scriptEngine_);
      RegisterAudioAPI(scriptEngine_);
      RegisterUIAPI(scriptEngine_);
      RegisterScriptAPI(scriptEngine_);
      RegisterEngineAPI(scriptEngine_);

      // Subscribe to console commands
      SetExecuteConsoleCommands(true);

  */
}

Script::~Script() {
  if (immediateContext_) {
    immediateContext_->Release();
    immediateContext_ = nullptr;
  }

  for (unsigned i = 0; i < scriptFileContexts_.size(); ++i)
    scriptFileContexts_[i]->Release();

  if (scriptEngine_) {
    scriptEngine_->Release();
    scriptEngine_ = nullptr;
  }
}

bool Script::Execute(const std::string &line) {
  int r;
  // Create a context that will execute the script.
  asIScriptContext *ctx = scriptEngine_->CreateContext();
  if (ctx == nullptr) {
    std::cout << "Failed to create the context." << std::endl;
    scriptEngine_->Release();
    return false;
  }

  // We don't want to allow the script to hang the application, e.g. with an
  // infinite loop, so we'll use the line callback function to set a timeout
  // that will abort the script after a certain time. Before executing the
  // script the timeOut variable will be set to the time when the script must
  // stop executing.
  // DWORD timeOut;
  // r = ctx->SetLineCallback(asFUNCTION(LineCallback), &timeOut, asCALL_CDECL);
  /*if( r < 0 )
{
    std::cout << "Failed to set the line callback function." << std::endl;
    ctx->Release();
    scriptEngine_->Release();
    return -1;
}*/

  // Find the function for the function we want to execute.
  asIScriptFunction *func =
      scriptEngine_->GetModule(nullptr)->GetFunctionByDecl(
          "float calc(float, float)");
  if (func == nullptr) {
    std::cout << "The function 'float calc(float, float)' was not found."
              << std::endl;
    ctx->Release();
    scriptEngine_->Release();
    return false;
  }

  // Prepare the script context with the function we wish to execute. Prepare()
  // must be called on the context before each new script function that will be
  // executed. Note, that if you intend to execute the same function several
  // times, it might be a good idea to store the function returned by
  // GetFunctionByDecl(), so that this relatively slow call can be skipped.
  r = ctx->Prepare(func);
  if (r < 0) {
    std::cout << "Failed to prepare the context." << std::endl;
    ctx->Release();
    scriptEngine_->Release();
    return false;
  }

  // Now we need to pass the parameters to the script function.
  ctx->SetArgFloat(0, 3.14159265359f);
  ctx->SetArgFloat(1, 2.71828182846f);

  // Set the timeout before executing the function. Give the function 1 sec
  // to return before we'll abort it.
  // timeOut = timeGetTime() + 1000;

  // Execute the function
  std::cout << "Executing the script." << std::endl;
  std::cout << "---" << std::endl;
  r = ctx->Execute();
  std::cout << "---" << std::endl;
  if (r != asEXECUTION_FINISHED) {
    // The execution didn't finish as we had planned. Determine why.
    if (r == asEXECUTION_ABORTED)
      std::cout << "The script was aborted before it could finish. Probably it "
                   "timed out."
                << std::endl;
    else if (r == asEXECUTION_EXCEPTION) {
      std::cout << "The script ended with an exception." << std::endl;

      // Write some information about the script exception
      asIScriptFunction *func = ctx->GetExceptionFunction();
      std::cout << "func: " << func->GetDeclaration() << std::endl;
      std::cout << "modl: " << func->GetModuleName() << std::endl;
      std::cout << "sect: " << func->GetScriptSectionName() << std::endl;
      std::cout << "line: " << ctx->GetExceptionLineNumber() << std::endl;
      std::cout << "desc: " << ctx->GetExceptionString() << std::endl;
    } else
      std::cout << "The script ended for some unforeseen reason (" << r << ")."
                << std::endl;
  } else {
    // Retrieve the return value from the context
    float returnValue = ctx->GetReturnFloat();
    std::cout << "The script function returned: " << returnValue << std::endl;
  }

  // We must release the contexts when no longer using them
  ctx->Release();

  // Shut down the engine
  // scriptEngine_->ShutDownAndRelease();

  return true;
}

bool Script::CompileScript(std::string file_name) {
  int r;

  // We will load the script from a file on the disk.
  using namespace std;
  FILE *f = fopen(file_name.c_str(), "rb");
  if (f == nullptr) {
    std::cout << "Failed to open the script file 'script.as'." << std::endl;
    return false;
  }

  // Determine the size of the file
  fseek(f, 0, SEEK_END);
  int len = ftell(f);
  fseek(f, 0, SEEK_SET);

  // On Win32 it is possible to do the following instead
  // int len = _filelength(_fileno(f));

  // Read the entire file
  string script;
  script.resize(len);
  size_t c = fread(&script[0], len, 1, f);
  fclose(f);

  if (c == 0) {
    std::cout << "Failed to load script file." << std::endl;
    return false;
  }

  // Add the script sections that will be compiled into executable code.
  // If we want to combine more than one file into the same script, then
  // we can call AddScriptSection() several times for the same module and
  // the script engine will treat them all as if they were one. The script
  // section name, will allow us to localize any errors in the script code.
  asIScriptModule *mod = scriptEngine_->GetModule(nullptr, asGM_ALWAYS_CREATE);
  r = mod->AddScriptSection("script", &script[0], len);
  if (r < 0) {
    std::cout << "AddScriptSection() failed" << std::endl;
    return false;
  }

  // Compile the script. If there are any compiler messages they will
  // be written to the message stream that we set right after creating the
  // script engine. If there are no errors, and no warnings, nothing will
  // be written to the stream.
  r = mod->Build();
  if (r < 0) {
    std::cout << "Build() failed" << std::endl;
    return false;
  }

  // The engine doesn't keep a copy of the script sections after Build() has
  // returned. So if the script needs to be recompiled, then all the script
  // sections must be added again.

  // If we want to have several scripts executing at different times but
  // that have no direct relation with each other, then we can compile them
  // into separate script modules. Each module use their own namespace and
  // scope, so function names, and global variables will not conflict with
  // each other.

  return true;
}

void Script::MessageCallback(const asSMessageInfo *msg, void *param) {
  const char *type = "ERR ";
  if (msg->type == asMSGTYPE_WARNING)
    type = "WARN";
  else if (msg->type == asMSGTYPE_INFORMATION)
    type = "INFO";

  printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type,
         msg->message);
}

void Script::ExceptionCallback(asIScriptContext *context) {
  std::string message;
  // message.append("- Exception '%s' in '%s'\n%s",
  // context->GetExceptionString(),
  //  context->GetExceptionFunction()->GetDeclaration(), GetCallStack(context));
  message += "- Exception '" + std::string(context->GetExceptionString()) +
             "' in '" + context->GetExceptionFunction()->GetDeclaration() +
             "'\n" + GetCallStack(context);

  asSMessageInfo msg{};
  msg.row = context->GetExceptionLineNumber(&msg.col, &msg.section);
  msg.type = asMSGTYPE_ERROR;
  msg.message = message.c_str();

  MessageCallback(&msg, nullptr);
}

std::string Script::GetCallStack(asIScriptContext *context) {
  std::string str("AngelScript callstack:\n");

  // Append the call stack
  for (asUINT i = 0; i < context->GetCallstackSize(); i++) {
    asIScriptFunction *func;
    const char *scriptSection;
    int line, column;
    func = context->GetFunction(i);
    line = context->GetLineNumber(i, &column, &scriptSection);
    str += "\t" + std::string(scriptSection) + ":" + func->GetDeclaration() +
           ":" + std::to_string(line) + "," + std::to_string(column) + "\n";
    // str.append("\t%s:%s:%d,%d\n", scriptSection, func->GetDeclaration(),
    // line, column);
  }

  return str;
}
