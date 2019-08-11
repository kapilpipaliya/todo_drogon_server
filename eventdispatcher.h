//#ifndef EVENTDISPATCHER_H
//#define EVENTDISPATCHER_H

//#include <string>
//#include <json/json.h>

////template <class TYPE >
//class EventHandler
//{
//public:
//    virtual void handleEvent(const Json::Value &)=0;

//    template <typename FUNCTION>
//    EventHandler(){
//        EventHandler::instance().registerHandler(TYPE, [this](const Json::Value &event){
//            this->handleEvent(event);
//        })
//    }

//    template <typename FUNCTION>
//    void registerHandler(const std::string &pathPattern,FUNCTION &&function)
//    {


//    }


//    static EventHandler &instance(){
//            static EventHandler _instance;
//            return _instance;
//    }

//    std::unordered_map<std::string, int> _connectionsNumMap;


//};

//#endif // EVENTDISPATCHER_H
