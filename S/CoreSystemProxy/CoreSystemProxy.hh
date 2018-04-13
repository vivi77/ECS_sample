#pragma once

#include "S/CoreSystemProxy/coresystemproxy_export.h"
#include "Entity/EntityManager.hh"
#include "CoreSystemData.hh"
#include <list>

namespace lel::ecs
{
  class Core;

  // This class serve as a proxy to the class Core
  //   It provides services that Core should provide. But it does not need to the
  //   users of theses services to include Core (which is not in a shared library)
  // TODO: Make it not use a static variable to store the system list.
  //    ==> Problem: Works like a global. Does not follow the willing of having
  //    several different 'Core' class (In this situation, all the 'Core'
  //    classes would share the same SystemContainer)
  class CORESYSTEMPROXY_EXPORT CoreSystemProxy
  {
  public:
    using SystemContainer = std::list<CoreSystemData>; //Core::'Container of the systems'

  public:
    static entity::EntityManager::EntityPtr createEntity(std::initializer_list<entity::EntityManager::ComponentPtr>);

  private:
    static void registerEntityInSystems(const std::shared_ptr<entity::Entity>& entity);
    static void setSystemsList(SystemContainer& systems);
    static void setEntityManager(entity::EntityManager& manager);

  private:
    static SystemContainer* _systems;
    static entity::EntityManager* _entityManager;

    friend Core;
  };
} /* !lel::ecs */

// setSystemsList is private to avoid other classes to misuse this class.
//  Only Core class should be able to access it
