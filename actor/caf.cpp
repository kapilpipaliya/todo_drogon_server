#include "caf.h"

MyCAF globalCAF;


MyCAF::MyCAF(): sys(cfg), self(sys)
{
    initialiseMainWector();
//auto mainactor = self->spawn<MainActor>();
}

void MyCAF::initialiseMainWector()
{
    mainactor = self->spawn<MainActor>();
}
