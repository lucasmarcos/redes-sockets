use std::net::{TcpListener, TcpStream};
use std::io::{Read, Write};

fn responder(pedido: &mut TcpStream) {
    let mut buffer = [0; 32];
    pedido.write("oi (do servidor)".as_bytes()).unwrap();
    pedido.read(&mut buffer).unwrap();

    println!("{}", std::str::from_utf8(&buffer).unwrap());
}

fn main() {
    let servidor = TcpListener::bind("0.0.0.0:3000").unwrap();
    for pedido in servidor.incoming() {
        responder(&mut pedido.unwrap());
    }
}