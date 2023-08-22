<?php
// Verifica se a solicitação HTTP é um POST
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    // Lê o conteúdo enviado no corpo da solicitação
    $dadosCSV = file_get_contents('php://input');
    
    // Verifica se há dados
    if (!empty($dadosCSV)) {
        // Decodifica o CSV em um array
        $linhas = explode("\n", $dadosCSV);
        $dados = [];
        
        foreach ($linhas as $linha) {
            $campos = str_getcsv($linha);
            $dados[] = $campos;
        }
        
        // Agora você tem os dados em $dados, que é um array de arrays (linhas do CSV)
        
        // Faça o que você precisa com os dados aqui
        // Por exemplo, você pode gravá-los em um banco de dados ou fazer algum processamento específico
        
        // Envia uma resposta de sucesso
        http_response_code(200);
        echo 'Dados recebidos com sucesso.';
    } else {
        // Se não houver dados, envia uma resposta de erro
        http_response_code(400);
        echo 'Nenhum dado foi enviado.';
    }
} else {
    // Se não for uma solicitação POST, envia uma resposta de erro
    http_response_code(405);
    echo 'Método não permitido. Esta página só aceita solicitações POST.';
}
?>
s