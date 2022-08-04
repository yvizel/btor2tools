#pragma once

#include "boolector/boolector.h"
#include "btor2parser/btor2parser.h"

extern "C" {
#include "aiger.h"
}

class Btor2Model
{
 public:
  Btor *btor;

  std::vector<BoolectorNode *> inputs;
  std::unordered_map<int64_t, BoolectorNode *> states;
  std::unordered_map<int64_t, BoolectorNode *> init;
  std::unordered_map<int64_t, BoolectorNode *> next;
  std::vector<BoolectorNode *> bad;
  std::vector<BoolectorNode *> constraints;

  std::unordered_map<int64_t, BoolectorNode *> nodes;
  std::unordered_map<int64_t, BoolectorSort> sorts;

  Btor2Model () : btor (boolector_new ()){};

  ~Btor2Model ()
  {
    for (auto kv : nodes)
    {
      boolector_release (btor, kv.second);
    }
    for (auto kv : sorts)
    {
      boolector_release_sort (btor, kv.second);
    }
    boolector_delete (btor);
  }

  BoolectorSort get_sort (int64_t id)
  {
    auto it = sorts.find (id);
    assert (it != sorts.end ());
    return it->second;
  }

  void add_sort (int64_t id, BoolectorSort sort)
  {
    assert (sorts.find(id)  == sorts.end ());
    sorts[id] = sort;
  }

  BoolectorNode *get_node (int64_t id)
  {
    auto it = nodes.find (id);
    if (it == nodes.end ())
    {
      it = nodes.find (-id);
      assert (it != nodes.end ());
      add_node (id, boolector_not (btor, it->second));
      return nodes[id];
    }
    return it->second;
  }

  void add_node (int64_t id, BoolectorNode *node)
  {
    assert (nodes.find(id) == nodes.end ());
    nodes[id] = node;
  }

  BoolectorNode *get_init (int64_t id)
  {
    auto it = init.find (id);
    return it != init.end () ? it->second : nullptr;
  }

  BoolectorNode *get_next (int64_t id)
  {
    auto it = next.find (id);
    return it != next.end () ? it->second : nullptr;
  }
};

void parse_btor2 (FILE *infile, Btor2Model &model);
aiger* generate_aiger (Btor2Model &model, bool ascii_mode, bool ignore_error);