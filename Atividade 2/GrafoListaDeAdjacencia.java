import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class GrafoListaDeAdjacencia {

    public final LinkedList<Character> vertices;
    public final LinkedList<Integer>[] listaDeAdjacencia;
    public final int quantidadeDeVertices;

    int clock;

    public enum cores {
        BRANCO,
        PRETO,
        CINZA
    }

    cores[] cor;

    Character[] parents;

    Integer[] descoberta;

    Integer[] distanciaFinal;

    public GrafoListaDeAdjacencia(Character[] vertices, String[] arestas) {
        this.vertices = new LinkedList<>(List.of(vertices));
        quantidadeDeVertices = this.vertices.size();

        listaDeAdjacencia = new LinkedList[quantidadeDeVertices];
        for (int i = 0; i < quantidadeDeVertices; i++) {
            listaDeAdjacencia[i] = new LinkedList<>();
        }

        for (String edge : arestas) {
            char vertex1 = edge.charAt(0);
            char vertex2 = edge.charAt(1);

            int indiceVertice1 = this.vertices.indexOf(vertex1);
            int indiceVertice2 = this.vertices.indexOf(vertex2);

            listaDeAdjacencia[indiceVertice1].add(indiceVertice2);
            listaDeAdjacencia[indiceVertice2].add(indiceVertice1);
        }
    }

    public void DFS(){
        this.cor = new cores[this.quantidadeDeVertices];
        this.parents = new Character[this.quantidadeDeVertices];
        this.descoberta = new Integer[this.quantidadeDeVertices];
        this.distanciaFinal = new Integer[this.quantidadeDeVertices];

        int hold = 0;
        for (char item: this.vertices) {
            this.cor[hold] = cores.BRANCO;
            this.parents[hold] = null;
            this.descoberta[hold] = 0;
            this.distanciaFinal[hold] = 0;
            hold++;
        }

        this.clock = 0;

        for (char item : this.vertices) {
            int u = this.vertices.indexOf(item);
            if(cor[u].equals(cores.BRANCO)){
                DFS_VISIT(u);
            }
        }

        printItems();
    }

    private void DFS_VISIT(int u) {
        this.cor[u] = cores.CINZA;
        this.clock++;
        this.descoberta[u] = this.clock;

        for (int v : this.listaDeAdjacencia[u]){
            if(cor[v].equals(cores.BRANCO)){
                this.parents[v] = this.vertices.get(u);
                DFS_VISIT(v);
            }
        }
        cor[u] = cores.PRETO;

        distanciaFinal[u] = ++this.clock;
    }

    void printItems(){
        System.out.println("Cores: " + Arrays.toString(this.cor));
        System.out.println("Distâncias: " + Arrays.toString(this.descoberta));
        System.out.println("Predencessores: " + Arrays.toString(this.parents));
        System.out.println("Tempo final: " + Arrays.toString(this.distanciaFinal));
    }

    @Override
    public String toString() {
        StringBuilder graph = new StringBuilder();

        for (int i = 0; i < quantidadeDeVertices; i++) {
            graph.append(vertices.get(i))
                    .append(": ");
            LinkedList<Integer> linkedList = listaDeAdjacencia[i];
            for (Integer index : linkedList) {
                graph.append(vertices.get(index))
                        .append(" ");
            }
            graph.append("\n");
        }

        return graph.toString();
    }
}