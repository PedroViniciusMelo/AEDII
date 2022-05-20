import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.stream.IntStream;

public class GrafoMatrizDeAdjacencia {

    private final LinkedList<Character> vertices;

    private final int[][] matrizDeAdjacencia;
    private final int quantidadeDeVertices;

    public GrafoMatrizDeAdjacencia(Character[] vertices, Aresta[] arestas) {
        this.vertices = new LinkedList<>(List.of(vertices));
        quantidadeDeVertices = this.vertices.size();

        matrizDeAdjacencia = new int[quantidadeDeVertices][quantidadeDeVertices];
        for (int i = 0; i < quantidadeDeVertices; i++) {
            for (int j = 0; j < quantidadeDeVertices; j++) {
                matrizDeAdjacencia[i][j] = 0;
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

    void MST_PRIM(Character s) throws NoSuchFieldException {
        int[] chaves = new int[this.quantidadeDeVertices];
        Character[] predecessores = new Character[this.quantidadeDeVertices];

        Arrays.fill(chaves, Integer.MAX_VALUE);
        Arrays.fill(predecessores, null);

        int selecionado = this.vertices.indexOf(s);

        if (selecionado == -1) {
            throw new NoSuchFieldException(s.toString());
        }

        chaves[selecionado] = 0;

        PriorityQueue<ArestaSimplificada> fila = new PriorityQueue<>();

        int count = 0;
        for (Character vertices : this.vertices) {
            fila.add(new ArestaSimplificada(vertices, chaves[count]));
            count++;
        }

        while (!fila.isEmpty()) {
            ArestaSimplificada aresta = fila.poll();
            int u = vertices.indexOf(aresta.aresta);

            for (int i = 0; i < this.quantidadeDeVertices; i++) {
                if (this.matrizDeAdjacencia[u][i] > 0) {
                    ArestaSimplificada hold = new ArestaSimplificada(vertices.get(i), 0);
                    if (fila.contains(hold) && this.matrizDeAdjacencia[u][i] < chaves[i]) {
                        predecessores[i] = this.vertices.get(u);
                        chaves[i] = this.matrizDeAdjacencia[u][i];

                        fila.remove(hold);
                        hold.chave = chaves[i];
                        fila.add(hold);
                    }
                }
            }
        }

        System.out.println("=-=-=-==-=-=- Prim's algorithm =-=-=-=-=-=-=-=\n");
        System.out.println("Predecessores :" + Arrays.toString(predecessores));
        System.out.println("Chaves :" + Arrays.toString(chaves));
        System.out.println("Soma dos pesos mínimos da árvore gerada: " + IntStream.of(chaves).sum() + "\n");
    }

    @Override
    public String toString() {
        StringBuilder grafo = new StringBuilder();

        grafo.append("\t");
        for (Character vertex : vertices) {
            grafo.append(vertex).append("\t");
        }

        grafo.append("\n");

        for (int i = 0; i < quantidadeDeVertices; i++) {
            grafo.append(vertices.get(i)).append("\t");
            for (int j = 0; j < quantidadeDeVertices; j++) {
                grafo.append(matrizDeAdjacencia[i][j]).append("\t");
            }
            grafo.append("\n");
        }
        return grafo.toString();
    }
}