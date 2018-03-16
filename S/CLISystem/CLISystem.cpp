#include "CLISystem.hh"
#include "CoreEvent.hh"
#include "EManager.hh"
#include <experimental/source_location>

CLISystem::CLISystem()
  : _cliproducer{}
  , _cliparser{_cliproducer}
  , _cmds{
    {
      "quit",
      [](const lel::CmdOutput&) -> void
      {
        EManager::fire<CoreEvent>(CoreEvent::Type::EXIT);
      }
    },
    {
      "add",
      [](const lel::CmdOutput& o) -> void
      {
        if (o.getArgs().size() != 1)
        {
          std::cout << "Usage: add <system name>\n";
          return ;
        }

        auto sysName = o.getArgs()[0]->getTerminal();
        EManager::fire<CoreEvent>(CoreEvent::Type::ADD_SYSTEM, sysName);
      }
    },
  } //CLISystem::_cmds end of initialization
{}

void CLISystem::exec()
{
  try
  {
    auto expr = _cliparser.parseExpression();

    if (expr->getType() != lel::CLIParserType::COMMAND)
    {
      std::cout << "This is not a command\n";
      return ;
    }

    auto cmd = std::static_pointer_cast<lel::CmdOutput>(expr);
    _cmds.exec(*cmd);
    _cliparser.consume(lel::CLIProducerType::EOL);
  }
  catch (const std::exception& e)
  {
    std::cerr << std::experimental::source_location::current().function_name()
      << ": " << e.what() << "\n";
    _cliparser.reset();
    return ;
  }
}
