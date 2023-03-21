public class Celular {
    private Comunicacao c;
    private Processador p;
    private Som s;
    private Tela t;
    private int bateria;
    Celular(){
       c = new Comunicacao();
       p = new Processador();
       s = new Som();
       t = new Tela();
    }

    private boolean has_battery(int gasto){
        if (bateria > gasto){
            bateria -= gasto;
            return true;
        }
        else{
            System.out.println("O celular esta descarregando. A ação não será executada por falta de bateria");
            return false;
        }

    }
    public void ligar_dispostivo(){
        bateria = 100;
        t.ligar_tela();
        c.conect_chip();
        c.conect_internet();
        c.conect_sinal();
    }

    public void enviar_mensagem(){
        if(has_battery(10) != false){
        System.out.println("Sistema de SMS!");
        System.out.println("Digite sua mensagem: ");
        String dados = t.le();

        System.out.println("Digite o numero ou contado que deseja enviar: ");
        String alvo = t.le();

        System.out.println("A mensagem '" + dados + "' foi enviada para " + alvo);
        }
    }

    public void music_player(){
        if(has_battery(10) != false){
        s.Ouvir_musica("Barões da pisadinha - Tá Rocheda");
        s.Aumentar_volume();
        s.Aumentar_volume();

        System.out.println("Envie sua sugestão de musica para a radio!!!");
        String dados = t.le();
        System.out.println(dados + " entrará na fila de reprodução");
        }
    }

    public void abrir_app(){
        if(has_battery(20) != false){
        System.out.println("Qual aplicativo deseja utilizar?");
        String dados = t.le();
        System.out.println("Abrindo " + dados + "...");
        p.add_use();
        System.out.println("O processamento usado está sendo de " + p.memoria_usada() + "%");
        }
    }

}
