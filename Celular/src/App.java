public class App {
    public static void main(String[] args) throws Exception {
        Celular MotoApple = new Celular();
        MotoApple.ligar_dispostivo();

        System.out.println("----------------------------------------------");
        MotoApple.enviar_mensagem();
        System.out.println("----------------------------------------------");
        MotoApple.music_player();
        System.out.println("----------------------------------------------");
        MotoApple.abrir_app();
        System.out.println("----------------------------------------------");
        MotoApple.abrir_app();
    }
}
