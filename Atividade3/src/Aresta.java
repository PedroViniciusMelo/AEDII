public class Aresta implements Comparable<Aresta>{
    int peso;

    Character inicio;

    Character fim;

    public Aresta(int peso, Character inicio, Character fim){
        this.peso = peso;
        this.inicio = inicio;
        this.fim = fim;
    }

    @Override
    public String toString() {
        return fim + "[" + this.peso + "]";
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

        return (this.inicio == aresta.inicio && this.fim == aresta.fim) || (this.fim == aresta.inicio && this.inicio == aresta.fim);
    }
}
