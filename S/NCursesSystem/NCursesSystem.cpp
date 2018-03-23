#include "NCursesSystem.hh"
#include "E/CLISystemEvent/CLISystemEvent.hh"
#include "E/EManager.hh"
#include "C/TerminalDrawable/TerminalDrawable.hh"
#include <curses.h>

#include "E/CoreEvent/CoreEvent.hh"
#include "Entity/EntityManager.hh"

void NCursesSystem::exec()
{
  char c = getch();
  if (c == 'q')
    EManager::fire<CoreEvent>(CoreEvent::Type::EXIT);
  else if (c == 'c')
  {
    EntityManager::createEntity({std::make_shared<TerminalDrawable>("c\na")});
  }

  int x = 0;
  for (auto& comp : _drawableComp)
  {
    mvprintw(comp.drawableComp->pos.y, comp.drawableComp->pos.x + x, comp.drawableComp->sym);
    ++x;
  }
  refresh();
}

void NCursesSystem::registerEntity(const EntityPtr& entity)
{
  NCursesData data;

  auto comps = entity->getComponents();
  for (auto& comp : comps)
  {
    if (comp->getID() == TerminalDrawable::getComponentID())
      data.drawableComp = std::static_pointer_cast<TerminalDrawable>(comp);
  }
  if (data.isValid())
    _drawableComp.emplace_back(data);
  refresh();
}

void NCursesSystem::setup()
{
  EManager::fire<CLISystemEvent>(CLISystemEvent::Type::DISABLE);
  initscr();
  cbreak();
  noecho();
}

void NCursesSystem::atRemove()
{
  endwin();
  EManager::fire<CLISystemEvent>(CLISystemEvent::Type::ENABLE);
}
