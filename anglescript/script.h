#ifndef SCRIPT_H
#define SCRIPT_H
#include <angelscript.h>
#include "thirdparty/angelscriptaddons/scriptarray/scriptarray.h"
#include "thirdparty/angelscriptaddons/scriptbuilder/scriptbuilder.h"
#include "thirdparty/angelscriptaddons/scriptstdstring/scriptstdstring.h"
#include <string>
#include <vector>
class Script
{
public:
    Script();
    /// Destruct. Release the AngelScript engine.
    ~Script();

    /// Compile and execute a line of script in immediate mode.
    virtual bool Execute(const std::string& line);
    bool CompileScript(std::string file_name);

    /// Set whether to execute engine console commands as script code.
    //void SetExecuteConsoleCommands(bool enable);

    /// Log a message from the script engine.
    void MessageCallback(const asSMessageInfo* msg, void *param); //done
    /// Handle a script exception.
    void ExceptionCallback(asIScriptContext* context);
    /// Get call stack.
    static std::string GetCallStack(asIScriptContext* context);

    /// Return the AngelScript engine.
    asIScriptEngine* GetScriptEngine() const { return scriptEngine_; } //done

    /// Return immediate execution script context.
    asIScriptContext* GetImmediateContext() const { return immediateContext_; } //done

    /// Return whether is executing engine console commands as script code.
   // bool GetExecuteConsoleCommands() const { return executeConsoleCommands_; } //done

    /// Clear the inbuild object type cache.
    //void ClearObjectTypeCache();
    /// Query for an inbuilt object type by constant declaration. Can not be used for script types.
   asITypeInfo* GetObjectType(const char* declaration); //done

    /// Return the script module create/delete mutex.
    //Mutex& GetModuleMutex() { return moduleMutex_; } //done

    /// Returns an array of strings of enum value names for Enum Attributes.
    //const char** GetEnumValues(int asTypeID);


private:
    /// Return a script function/method execution context for the current execution nesting level.
    asIScriptContext* GetScriptFileContext();
    /// AngelScript engine.
    asIScriptEngine* scriptEngine_;
    /// Immediate execution script context.
    asIScriptContext* immediateContext_;
    /// Script function/method execution contexts.
    std::vector<asIScriptContext*> scriptFileContexts_;
    /// Current script execution nesting level.
    unsigned scriptNestingLevel_;
    /// Flag for executing engine console commands as script code. Default to true.
    bool executeConsoleCommands_;
};

#endif // SCRIPT_H
