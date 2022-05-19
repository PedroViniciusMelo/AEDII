import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class GrafoMatrizDeAdjacencia {

    private final LinkedList<Character> vertices;

    private final int[][] matrizDeAdjacencia;
    private final int quantidadeDeVertices;

    public enum cores {
        PRETO,
        CINZA,
        BRANCO
    }

    public GrafoMatrizDeAdjacencia(Character[] vertices, Aresta[] arestas) {
        this.vertices = new LinkedList<>(List.of(vertices));
        quantidadeDeVertices = this.vertices.size();

        matrizDeAdjacencia = new int[quantidadeDeVertices][quantidadeDeVertices];
        for (int i = 0; i < quantidadeDeVertices; i++) {
            for (int j = 0; j < quantidadeDeVertices; j++) {
                if (i == j) {
                    matrizDeAdjacencia[i][j] = 1;
                } else {
                    matrizDeAdjacencia[i][j] = 0;
                }
            }
        }

        //Carregamento das arestas
        for (Aresta aresta : arestas) {
            int posicaoVertice1 = this.vertices.indexOf(aresta.inicio);
            int posicaoVertice2 = this.vertices.indexOf(aresta.fim);

            matrizDeAdjacencia[posicaoVertice1][posicaoVertice2] = aresta.peso;
            matrizDeAdjacencia[posicaoVertice2][posicaoVertice1] = aresta.peso;
        }
    }

    void printItems(cores[] matrizCores, Integer[] matrizDistancias, Character[] matrizParents){
        System.out.println("Cores: " + Arrays.toString(matrizCores));
        System.out.println("Distâncias: " + Arrays.toString(matrizDistancias));
        System.out.println("Predencessores: " + Arrays.toString(matrizParents));
    }

    int menor(LinkedList<Integer> list){
        if(list.isEmpty()){
          return -1;
        }
        int menor = list.get(0);
        int indice = 0;
        int count = 0;
        for (int item : list) {
            if(item < menor){
                menor = item;
                indice = count;
            }
            count++;
        }

        list.remove(indice);
        return menor;
    }

    LinkedList<Aresta> getVizinhos(int s){
        LinkedList<Aresta> vizinhos = new LinkedList<>();
        for(int i = 0; i < this.quantidadeDeVertices; i++){
            if(this.matrizDeAdjacencia[s][i] > 0 && i != s){
                vizinhos.add(new Aresta(this.matrizDeAdjacencia[s][i], this.vertices.get(s), this.vertices.get(i)));
            }
        }
        return vizinhos;
    }

    void MST_PRIM(char s) {
        int[] chaves = new int[this.quantidadeDeVertices];
        Character[] parents = new Character[this.quantidadeDeVertices];

        Arrays.fill(chaves, Integer.MAX_VALUE);
        Arrays.fill(parents, null);

        int selecionado = this.vertices.indexOf(s);

        if(selecionado == -1){
            return;
        }

        chaves[selecionado] = 0;

        LinkedList<Integer> fila = new LinkedList<>();
        fila.add(selecionado);
        for (int i = 0; i < quantidadeDeVertices; i++){
            if(i != selecionado){
                fila.add(i);
            }
        }


        while (!fila.isEmpty()) {
            int min = menor(fila);

            for (Aresta aresta : getVizinhos(min)) {
                int indexFim = this.vertices.indexOf(aresta.fim);
                if(fila.contains(indexFim) && aresta.peso < chaves[indexFim]){
                    parents[indexFim] = this.vertices.get(min);
                    chaves[indexFim] = aresta.peso;
                }
            }
        }
        System.out.println("Parents :" + Arrays.toString(parents));
        System.out.println("Keys :" + Arrays.toString(chaves));
    }

    @Override
    public String toString() {
        StringBuilder grafo = new StringBuilder();

        grafo.append("\t");
        for (Character vertex : vertices) {
            grafo.append(vertex)
                    .append("\t");
        }
        grafo.append("\n");

        for (int i = 0; i < quantidadeDeVertices; i++) {
            grafo.append(vertices.get(i))
                    .append("\t");
            for (int j = 0; j < quantidadeDeVertices; j++) {
                grafo.append(matrizDeAdjacencia[i][j])
                        .append("\t");
            }
            grafo.append("\n");
        }
        return grafo.toString();
    }
}