#pragma once

#define EngineExport  __declspec( dllexport )

namespace Oyun
{
    template <typename T>
    class EngineExport EngineSubsytem
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
