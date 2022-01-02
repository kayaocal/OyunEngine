#ifndef __OYUN_CORE__
#define __OYUN_CORE__

#include "Subsystems/SerializationSubsystem.h"
#include <iostream>


#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif


namespace Oyun
{
	class OYUN_API BaseClass
	{

	};

    class OYUN_API BaseStaticClass
    {
    public:
        virtual BaseClass* Instantiator() = 0;
    };

}


#define OYUNCLASS(BASE)\
class OYUN_API Static##BASE : public Oyun::BaseStaticClass{\
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
