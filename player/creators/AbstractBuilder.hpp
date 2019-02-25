#pragma once

#include <memory>

template<typename Builder>
struct BuilderTraits;

template<typename Builder>
class AbstractBuilder
{
public:
    using Options = typename BuilderTraits<Builder>::Options;
    using Component = typename BuilderTraits<Builder>::Component;
    using Handler = typename BuilderTraits<Builder>::Handler;

    AbstractBuilder() = default;
    virtual ~AbstractBuilder() = default;

    std::unique_ptr<Component> build()
    {
        auto component = create();
        doSetup(*component);
        return component;
    }

    Builder& options(const Options& opts)
    {
        m_options = std::make_unique<Options>(opts);
        retrieveOptions(opts);
        return static_cast<Builder&>(*this);
    }

    Builder& adaptor(std::unique_ptr<Handler>&& adaptor)
    {
        m_adaptor = std::move(adaptor);
        return static_cast<Builder&>(*this);
    }

protected:
    virtual void retrieveOptions(const typename BuilderTraits<Builder>::Options& opts) = 0;
    virtual std::unique_ptr<Component> create() = 0;
    virtual std::unique_ptr<Handler> createDefaultHandler() = 0;
    virtual void doSetup(typename BuilderTraits<Builder>::Component&) { }

    std::unique_ptr<Handler> createHandler()
    {
        if(!m_adaptor) return createDefaultHandler();

        return std::move(m_adaptor);
    }

protected: // FIXME
    std::unique_ptr<Options> m_options;
    std::unique_ptr<Handler> m_adaptor;

};
