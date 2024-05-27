#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include "i_o_processing.hpp"
#include <fstream>
#include <experimental/filesystem>
#include <iomanip>
#include <stream_guard.hpp>

void basic_graph_print(std::ostream& out, const zaitsev::graph_t& graph, size_t indnent_sz = 2)
{
  using namespace zaitsev;
  std::string indent(indnent_sz, ' ');
  out << "Verti�es (" << graph.size() << "):\n";
  size_t counter = 0;
  for (graph_t::const_iterator it = graph.cbegin(); it != graph.cend(); ++it)
  {
    out << indent << it->first << '\n';
    counter += it->second.size();
  }
  out << "Edges (" << counter << "):\n";
  for (graph_t::const_iterator it_g = graph.cbegin(); it_g != graph.cend(); ++it_g)
  {
    for (unit_t::const_iterator it_v = it_g->second.cbegin(); it_v != it_g->second.cbegin(); ++it_v)
    {
      out << indent << it_g->first << " --> " << it_v->first << " : " << it_v->second << '\n';
    }
  }
}

std::ostream& zaitsev::list_of_graphs(std::ostream& out, base_t& graphs)
{
  if (graphs.empty())
  {
    return out << "No saved graphs\n";
  }
  zaitsev::StreamGuard guard(out);
  auto c_it = graphs.cbegin();
  for (size_t i = 0; i < graphs.size(); ++i)
  {
    out << std::setw(3) << i << ". ";
    out << c_it->first << '\n';
  }
  return out;
}

void zaitsev::print_help()
{
  using namespace std;
  string indent(2, ' ');
  cout << "Help:\n";
  cout << "1.  read <file> <graph-name>\n" << indent;
  cout << "Read the graph from the file <file>, and assign it the name <graph-name>.\n\n";
  cout << "2.  write <graph> <file>\n" << indent;
  cout << "Write a graph <graph>  to a file <file>.\n\n";
  cout << "3.  list_of_graphs\n" << indent;
  cout << "Output a lexicographically ordered list of available graphs.\n\n";
  cout << "4.  print <graph-name>\n" << indent;
  cout << "Print a description of the graph <graph-name>.\n\n";
  cout << "5.  create_graph <graph-name>\n" << indent;
  cout << "Create an empty graph named <graph-name>.\n\n";
  cout << "6.  delete_graph <graph>\n" << indent;
  cout << "Delete a graph named <graph-name>.\n\n";
  cout << "7.  add_vertex <graph> <vertex>  \n" << indent;
  cout << "Add a vertex <vertex> to the graph <graph-name>.\n\n";
  cout << "8.  add_edge [-check] <graph> <begin> <end> <value>\n" << indent;
  cout << "Add an edge to the graph <graph> that connects the vertices <begin> <end> with the value <value>.\n\n";
  cout << "9.  merge [-check] <new-graph> <graph-1> <graph-2> \n" << indent;
  cout << "A new graph <new-graph> is created, which is a union of graphs <graph-1> and <graph-2>.\n\n";
  cout << "10. negative_weight_cycles <graph>\n" << indent;
  cout << "Output a lexicographically ordered list of available graphs.\n\n"; //to do
  cout << "11. shortest <graph> <begin> <end>\n" << indent;
  cout << "Calculate the length of the shortest path from <begin> to <end> in the graph <graph>.\n\n";
  cout << "12. shortest_trace <graph> <vertex-begin> <vertex-end>\n" << indent;
  cout << "Print the shortest path from <begin> to <end> in the graph <graph>.\n\n";
  cout << "13. shortest_path_matrix <graph>\n" << indent;
  cout << "Output a lexicographically ordered list of available graphs.\n\n"; //to do
  cout << "14. dump <file>\n" << indent;
  cout << "Create a file <file> in which all graphs saved in the program are written.\n\n";
  return;
}

std::ostream& zaitsev::print_graph(std::istream& in, std::ostream& out, const base_t& graphs)
{
  std::string graph_name;
  in >> graph_name;
  base_t::const_iterator graph = graphs.find(graph_name);
  if (graph != graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + graph_name + "\", doesn't exists.");
  }
  out << "Graph name: " << graph->first << '\n';
  basic_graph_print(out, graph->second);
  return out;
}

void zaitsev::dump(const base_t& graphs)
{
  std::string file;
  if (std::experimental::filesystem::exists(file))
  {
    throw std::invalid_argument("File already exists");
  }

  std::ofstream out(file);
  out << "Graphs number - " << graphs.size() << '\n';
  for (base_t::const_iterator it = graphs.cbegin(); it != graphs.cend(); ++it)
  {
    out << "Graph name: " << it->first << '\n';
    basic_graph_print(out, it->second);
    out << '\n';
  }
  return;
}