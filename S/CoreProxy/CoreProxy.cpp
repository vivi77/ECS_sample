#include "CoreProxy.hh"
#include "E/EntityManagerEvent/EntityManagerEvent.hh"
#include "S/IS.hh"

namespace
{
  template <typename Fct>
  inline void applyOnSystemVector(lel::ecs::CoreProxy::SystemContainer& systems, Fct&& fct)
  {
    std::for_each(std::begin(systems), std::end(systems), std::forward<Fct>(fct));
  }
} /* ! */

namespace lel::ecs
{
  CoreProxy::CoreProxy(SystemContainer& systems, entity::EntityManager& manager, event::EManager& eventManager)
    : _systems{systems}
    , _entityManager{manager}
    , _eventManager{eventManager}
  {}

  entity::EntityManager::EntityPtr CoreProxy::createEntity(std::initializer_list<entity::EntityManager::ComponentPtr> il)
  {
    auto entity = _entityManager.createEntity(il);
    std::for_each(std::begin(_systems), std::end(_systems),
                  [&entity](auto& data) { data.sys->registerEntity(entity); });
    _eventManager.fire<event::EntityManagerEvent>(event::EntityManagerEvent::Type::ENTITY_CREATED, entity->getID());
    return entity;
  }

  void CoreProxy::destroyEntity(const entity::EntityManager::ID id)
  {
    // TODO: Remove Entity from systems
    auto eventType = event::EntityManagerEvent::Type::ENTITY_NOT_FOUND;

    // TODO[HIGH PRIORITY]: Implement fetchEntity with a cache system.
    //auto entityToDelete = _entityManager.fetchEntity(id);
    //if (entityToDelete != nullptr)
    //{
    //  for (auto& data : _systems)
    //    data.sys->deregisterEntity(entityToDelete);
    //std::for_each(std::begin(_systems), std::end(_systems),
                  //[&entityToDelete](auto& data)
                  //{
                    //data.sys->registerEntity(entityToDelete);
                  //});

    if (_entityManager.destroyEntity(id))
      eventType = event::EntityManagerEvent::Type::ENTITY_DESTROYED;
    //}
    _eventManager.fire<event::EntityManagerEvent>(eventType, id);
  }
} /* !lel::ecs */
