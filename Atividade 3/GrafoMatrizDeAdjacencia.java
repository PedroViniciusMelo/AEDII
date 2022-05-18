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
            char vertice1 = aresta.aresta.charAt(0);
            char vertice2 = aresta.aresta.charAt(1);

            int posicaoVertice1 = this.vertices.indexOf(vertice1);
            int posicaoVertice2 = this.vertices.indexOf(vertice2);

            matrizDeAdjacencia[posicaoVertice1][posicaoVertice2] = aresta.peso;
            matrizDeAdjacencia[posicaoVertice2][posicaoVertice1] = aresta.peso;
        }
    }

    void printItems(cores[] matrizCores, Integer[] matrizDistancias, Character[] matrizParents){
        System.out.println("Cores: " + Arrays.toString(matrizCores));
        System.out.println("Distâncias: " + Arrays.toString(matrizDistancias));
        System.out.println("Predencessores: " + Arrays.toString(matrizParents));
    }

    void BFS(char s) {

        cores[] cor = new cores[quantidadeDeVertices];
        Integer[] distancia = new Integer[quantidadeDeVertices];
        Character[] pais = new Character[quantidadeDeVertices];


        int hold = 0;
        for (char item: vertices) {
            cor[hold] = cores.BRANCO;
            distancia[hold] = Integer.MAX_VALUE;
            pais[hold] = null;
            hold++;
        }


        int currentIndex = vertices.indexOf(s);
        if(currentIndex == -1){
            return;
        }

        cor[currentIndex] = cores.CINZA;
        distancia[currentIndex] = 0;

        LinkedList<Integer> fila = new LinkedList<>();
        fila.add(currentIndex);

        while (fila.size() != 0)
        {
            int u = fila.poll();

            //Variável de incremento
            int verticePosition = 0;
            for (int v: matrizDeAdjacencia[u]) {
                if(v == 1 && cor[verticePosition].equals(cores.BRANCO)){
                    cor[verticePosition] = cores.CINZA;
                    distancia[verticePosition] = distancia[u] + 1;
                    pais[verticePosition] = vertices.get(u);
                    fila.add(verticePosition);
                }
                verticePosition++;
            }
            cor[u] = cores.PRETO;
        }

        printItems(cor, distancia, pais);
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