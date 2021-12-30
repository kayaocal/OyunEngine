#ifndef __OYUN_CORE__
#define __OYUN_CORE__

#include "subsystems/SerializationSubsystem.h"
#include <iostream>
#include <typeinfo>
#include <typeindex>
namespace Oyun
{
	class BaseClass
	{

	};

    class BaseStaticClass
    {
    public:
        virtual BaseClass* Instantiator() = 0;
    };

}


#define OYUNCLASS(BASE)\
class Static##BASE : public Oyun::BaseStaticClass{\
public:\
    std::type_index mainClassIndex = std::type_index(typeid(Static##BASE));\
    std::string mainClassName = typeid(BASE).name();\
    using MainClassType = BASE ;\
    Static##BASE() {\
        std::cout << "BASE: " << mainClassName << std::endl;\
        Oyun::SerializationSubsystem::Get().Assign(mainClassName, this);\
    }\
    virtual Oyun::BaseClass* Instantiator() override\
    {\
        return new MainClassType();\
    }\
    \
    };\
\
    static Static##BASE StaticClass;

#define INIT_CLASS(CLASSNAME)\
CLASSNAME::Static##CLASSNAME S##CLASSNAME = CLASSNAME::Static##CLASSNAME();


#endif//__OYUN_CORE__
