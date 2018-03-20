#pragma once

#include "S/CRTPS.hpp"
#include "parsing/CLIParser.hh"
#include "parsing/CLIParserOutputs.hh"
#include "E/IEListener.hh"
#include <functional>

class CmdManager
{
public:
  using Command = std::string;
  using Callback = std::function<void(const lel::CmdOutput&)>;

public:
  CmdManager(std::initializer_list<std::unordered_map<Command, Callback>::value_type> l)
    : _actions{l}
  {}

  void exec(const lel::CmdOutput& output)
  {
    auto it = _actions.find(output.getCommand());
    if (it == std::end(_actions))
      std::cout << "Unknown command '" << output.getCommand() << "'\n";
    else
      it->second(output);
  }

private:
  std::unordered_map<Command, Callback> _actions;
};

class CLISystem : public CRTPS<CLISystem>, public IEListener
{
public:
  CLISystem();
  virtual ~CLISystem() = default;
  void exec() override;
  void registerEntity(const EntityPtr&) override;
  void setup() override;
  void atRemove() override;

  void update(const EPtr&) override;

private:
  lel::CLIProducer _cliproducer;
  lel::CLIParser _cliparser;
  CmdManager _cmds;
  bool _enabled = true;
};
