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
        // Diretório de saída para os dados
        $diretorioSaida = 'dados/';
        if (!is_dir($diretorioSaida)) {
            mkdir($diretorioSaida, 0777, true);
        }
        // Exporta os dados para um arquivo CSV no diretório especificado
        $nomeArquivo = $diretorioSaida . 'dados_exportados.csv';
        $csvContent = '';
        
        foreach ($dados as $linha) {
            $csvContent .= implode(',', $linha) . "\n";
        }
        
        file_put_contents($nomeArquivo, $csvContent);
        // Envia uma resposta de sucesso
        http_response_code(200);
        echo 'Dados exportados com sucesso e salvos em ' . $nomeArquivo;
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