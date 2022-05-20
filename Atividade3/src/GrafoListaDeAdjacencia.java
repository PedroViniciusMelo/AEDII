import java.util.*;
import java.util.stream.Collectors;

public class GrafoListaDeAdjacencia {
    public final LinkedList<Character> vertices;
    public final Map<Character, LinkedList<Aresta>> listaDeAdjacencia;
    public final int quantidadeDeVertices;

    public GrafoListaDeAdjacencia(Character[] vertices, Aresta[] arestas) {
        this.vertices = new LinkedList<>(List.of(vertices));
        quantidadeDeVertices = this.vertices.size();

        listaDeAdjacencia = new HashMap<>();
        for (char vertice: this.vertices) {
            this.listaDeAdjacencia.put(vertice, new LinkedList<>());
        }

        for (Aresta aresta : arestas) {
            this.listaDeAdjacencia
                    .get(aresta.inicio)
                    .add(new Aresta(aresta.peso, aresta.inicio, aresta.fim));
            this.listaDeAdjacencia
                    .get(aresta.fim)
                    .add(new Aresta(aresta.peso, aresta.inicio, aresta.fim));
        }
    }
    private String find(Set<String> conjuntos, Character vertice) throws NoSuchFieldException {
        for (String conjunto : conjuntos) {
            if(conjunto.contains(vertice.toString()))
                return conjunto;
        }

        throw new NoSuchFieldException(vertices.toString());
    }

    private void uniao(Set<String> subsets, String x, String y) {
        subsets.remove(x);
        subsets.remove(y);
        subsets.add(x + y);
    }


    public void MST_KRUSKAL() throws NoSuchFieldException {
        Set<String> conjuntos = new HashSet<>();
        LinkedList<Aresta> arestas = new LinkedList<>();
        LinkedList<Aresta> resultado = new LinkedList<>();

        for (Character item: vertices) {
            conjuntos.add(item.toString());
        }

        for (Map.Entry<Character, LinkedList<Aresta>> lista : this.listaDeAdjacencia.entrySet()) {
            for (Aresta aresta : lista.getValue()){
                if(!arestas.contains(aresta)){
                    arestas.add(aresta);
                }
            }
        }

        Collections.sort(arestas);

        for (Aresta aresta : arestas) {
            String x = find(conjuntos, aresta.inicio);
            String y = find(conjuntos, aresta.fim);

            if (!x.equals(y)) {
                resultado.add(aresta);
                uniao(conjuntos, x, y);
            }
        }

        System.out.println("Conjunto final :" + conjuntos);
        System.out.println("Árvore gerada :" + resultado);
        ArrayList<Integer> pesos = resultado.stream()
                .map(Aresta::getPeso)
                .collect(Collectors.toCollection(ArrayList::new));
        System.out.println("Soma dos pesos mínimos da árvore gerada: " + pesos.stream().mapToInt(Integer::intValue).sum() + "\n");
    }

   @Override
    public String toString() {
        StringBuilder graph = new StringBuilder();

       for (Character vertice: this.vertices) {
           graph.append(vertice).append(": ");
           LinkedList<Aresta> linkedList = this.listaDeAdjacencia.get(vertice);
           for (Aresta index : linkedList) {
               String info = index.fim + "[" + index.peso + "]";
               graph.append(" ").append(info).append('\t');
           }
           graph.append("\n");
       }
        return graph.toString();
    }
}