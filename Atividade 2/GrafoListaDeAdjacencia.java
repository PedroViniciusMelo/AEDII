import java.util.*;

public class GrafoListaDeAdjacencia {

    private final LinkedList<Character> vertices;
    private final Map<Character, LinkedList<Character>> listaDeAdjacencia;
    private final int quantidadeDeVertices;

    int clock;

    public enum cores {
        BRANCO,
        PRETO,
        CINZA
    }

    Map<Character, cores> cor;

    Map<Character, Character> predecessores;

    Map<Character, Integer> descoberta;

    Map<Character, Integer> distanciaFinal;

    public GrafoListaDeAdjacencia(Character[] vertices, String[] arestas) {
        this.vertices = new LinkedList<>(List.of(vertices));
        quantidadeDeVertices = this.vertices.size();

        listaDeAdjacencia = new HashMap<>();

        for (Character vertice: this.vertices) {
            this.listaDeAdjacencia.put(vertice, new LinkedList<>());
        }

        for (String aresta : arestas) {
            char inicio = aresta.charAt(0);
            char fim = aresta.charAt(1);

            this.listaDeAdjacencia
                    .get(inicio)
                    .add(fim);
            this.listaDeAdjacencia
                    .get(fim)
                    .add(inicio);
        }
    }

    public void DFS(){
        this.cor = new HashMap<>();
        this.predecessores = new HashMap<>();
        this.descoberta = new HashMap<>();
        this.distanciaFinal = new HashMap<>();

        for (Character item: this.vertices) {
            this.cor.put(item, cores.BRANCO);
            this.predecessores.put(item, null);
            this.descoberta.put(item, 0);
            this.distanciaFinal.put(item, 0);
        }

        this.clock = 0;

        for (Character item : this.vertices) {
            if(cor.get(item).equals(cores.BRANCO)){
                DFS_VISIT(item);
            }
        }

        printItems();
    }

    private void printItems(){
        System.out.println("=-=-=-=-=-=- Busca em profundidade =-=-=-=-=-=-=- \n");
        System.out.println("Cores: " + cor.values());
        System.out.println("Distâncias: " + descoberta.values());
        System.out.println("Predecessores: " + predecessores.values());
        System.out.println("Tempo final: " + distanciaFinal.values() + "\n");
    }

    private void DFS_VISIT(Character u) {
        this.cor.put(u, cores.CINZA);
        this.clock++;
        this.descoberta.put(u, this.clock);

        for (Character v : this.listaDeAdjacencia.get(u)) {
            if(this.cor.get(v).equals(cores.BRANCO)){
                this.predecessores.put(v, u);
                DFS_VISIT(v);
            }
        }
        this.cor.put(u, cores.PRETO);

        this.distanciaFinal.put(u, ++this.clock);
    }

    @Override
    public String toString() {
        StringBuilder graph = new StringBuilder();

        for (Character vertice : this.vertices) {
            graph.append(vertice).append(": ");
            for (Character vertice2 : this.listaDeAdjacencia.get(vertice)){
                graph.append(vertice2).append(" ");
            }
            graph.append("\n");
        }

        return graph.toString();
    }
}