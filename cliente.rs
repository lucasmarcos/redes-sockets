use std::net::TcpStream;
use std::io::{Read, Write};

fn enviar(conexao: &mut TcpStream) {
    let mut buffer = [0; 32];
    conexao.write("oi (do cliente)".as_bytes()).unwrap();
    conexao.read(&mut buffer).unwrap();

    println!("{}", std::str::from_utf8(&buffer).unwrap());
}

fn main() {
    let mut conexao = TcpStream::connect("127.0.0.1:3000").unwrap();
    enviar(&mut conexao);
}