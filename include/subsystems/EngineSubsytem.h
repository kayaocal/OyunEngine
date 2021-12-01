#ifndef OYUN_ENGINE_SUBSYSTEM_H__
#define OYUN_ENGINE_SUBSYSTEM_H__

#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif

namespace Oyun
{
    template <typename T>
    class OYUN_API EngineSubsytem
    {

    public:
        EngineSubsytem(const EngineSubsytem<T>&) = delete;
        EngineSubsytem(EngineSubsytem<T>&&) = delete;


        EngineSubsytem(){}
        virtual ~EngineSubsytem() {}

        virtual void StartUp() = 0;
        virtual void ShutDown() = 0;
    };

}
#endif //OYUN_ENGINE_SUBSYSTEM_H__