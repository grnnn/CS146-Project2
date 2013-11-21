#ifndef RESOURCEHOLDER_HPP_INCLUDED
#define RESOURCEHOLDER_HPP_INCLUDED

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>


template <typename Resource, typename Identifier>
class ResourceHolder
{
    public:
        void                                             load(Identifier id, const std::string& filename);
        template <typename Parameter>
        void                                             load(Identifier id, const std::string& filename, const Parameter& secondParam);

        Resource&                                        get(Identifier id);
        const Resource&                                  get(Identifier id) const;


    private:
        void                                             insertResource(Identifier id, std::unique_ptr<Resource> resource);
    private:
        std::map<Identifier, std::unique_ptr<Resource>>  mResourceMap;
};

#include "..\resources\ResourceHolder.inl"

#endif // RESOURCEHOLDER_HPP_INCLUDED