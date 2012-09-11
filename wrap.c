#include <linear.h>
#include <stdlib.h>

#include "wrap.h"

feature_node_t *nodes_new(size_t n)
{
  feature_node_t *nodes = malloc((n + 1) * sizeof(feature_node_t));

  // Terminator
  nodes[n].index = -1;
  nodes[n].value = 0.0;

  return nodes;
}

void nodes_free(feature_node_t *nodes)
{
  free(nodes);
}

void nodes_put(feature_node_t *nodes, size_t nodes_idx, int idx,
  double value)
{
  nodes[nodes_idx].index = idx;
  nodes[nodes_idx].value = value;
}

problem_t *problem_new()
{
  problem_t *problem = malloc(sizeof(problem_t));

  problem->l = 0;
  problem->n = 0;
  problem->bias = -1;
  problem->y = malloc(0);
  problem->x = malloc(0);

  return problem;
}

void problem_free(problem_t *problem)
{
  free(problem->x);
  free(problem->y);
  free(problem);
}

void problem_add_train_inst(problem_t *problem, feature_node_t *nodes,
  double label)
{
  ++problem->l;

  // The number of features equals the highest feature index.
  feature_node_t *node;
  for (node = nodes; node->index != -1; ++node)
  	if (node->index > problem->n)
  		problem->n = node->index;

  problem->y = realloc(problem->y, problem->l * sizeof(double));
  problem->y[problem->l - 1] = label;
  problem->x = realloc(problem->x, problem->l * sizeof(feature_node_t *));
  problem->x[problem->l - 1] = nodes;
}