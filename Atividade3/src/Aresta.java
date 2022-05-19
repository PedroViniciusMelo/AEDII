public class Aresta implements Comparable<Aresta>{
    int peso;

    Character vertice1;

    Character vertice2;

    public Aresta(int peso, Character vertice1, Character vertice2){
        this.peso = peso;
        this.vertice1 = vertice1;
        this.vertice2 = vertice2;
    }

    @Override
    public String toString() {
        return vertice2 + "[" + this.peso + "]";
    }


    @Override
    public int compareTo(Aresta aresta) {
        return Integer.compare(this.peso, aresta.peso);
    }

    @Override
    public boolean equals(Object o) {
        if (o == this) {
            return true;
        }

        if (!(o instanceof Aresta)) {
            return false;
        }

        Aresta aresta = (Aresta) o;

        return (this.vertice1 == aresta.vertice1 && this.vertice2 == aresta.vertice2) || (this.vertice2 == aresta.vertice1 && this.vertice1 == aresta.vertice2);
    }
}
