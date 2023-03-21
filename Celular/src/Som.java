public class Som {
    int volume;
    Som(){
        volume = 0;
    }
    public void Aumentar_volume(){
        if(is_maxmin() != 1){
        
            volume += 1;
            System.out.println("Seu volume agora é " + volume);
        }
        else{
            System.out.println("Volume ja está no maximo..");
        }
    }

    public void Diminuir_volume(){
        if(is_maxmin() != -1){
        volume -= 1;
            System.out.println("Seu volume é " + volume);
        }
        else{
            System.out.println("Volume ja está no minimo..");
        }
    }

    private int is_maxmin(){
        if(volume == 10){
            
            return 1;
        }
        if(volume == 0){
           
            return -1;
        }

        return 0;
    }

    public void Ouvir_musica(String musica){
        System.out.println("Ouvindo agora mesmo " + musica + " na radio CAASO, a melhor da america latina");
    }
}
