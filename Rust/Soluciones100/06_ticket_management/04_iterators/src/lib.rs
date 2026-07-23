use ticket_fields::{TicketDescription, TicketTitle};

// TODO: Let's start sketching our ticket store!
//  First task: implement `IntoIterator` on `TicketStore` to allow iterating over all the tickets
//  it contains using a `for` loop.
//
// Hint: you shouldn't have to implement the `Iterator` trait in this case.
//   You want to *delegate* the iteration to the `Vec<Ticket>` field in `TicketStore`.
//   Look at the standard library documentation for `Vec` to find the right type
//   to return from `into_iter`.
#[derive(Clone)]
pub struct TicketStore {
    tickets: Vec<Ticket>,
}

#[derive(Clone, Debug, PartialEq)]
pub struct Ticket {
    pub title: TicketTitle,
    pub description: TicketDescription,
    pub status: Status,
}

#[derive(Clone, Debug, Copy, PartialEq)]
pub enum Status {
    ToDo,
    InProgress,
    Done,
}

impl TicketStore {
    pub fn new() -> Self {
        Self {
            tickets: Vec::new(),
        }
    }

    pub fn add_ticket(&mut self, ticket: Ticket) {
        self.tickets.push(ticket);
    }

    pub fn into_iter(self) -> std::vec::IntoIter<Ticket>{
        self.tickets.into_iter()
    }

}

/*NOTA! esto no hace falta para nada en estos tests! SOLO se emplea si se mete la Struct en un

let tienda = TicketStore::new();
for i in tienda. Ahi si que se necesita la implementacion de IntoIterator */
impl IntoIterator for TicketStore{
    type Item = Ticket; //es lo que devuelve el iterador *it que es un tickets: Vec<Ticket>,
    /*Nos dicen que no tenemos que implementar un Iterator nuevo sino usar el de Vec que existe
    por lo tanto para saber cual es el iterador de Vec nos vamos a la documentacion en std.rs
    y buscamos "Vec" como struct y nos vamos a la seccion de Traits, llegando a:
    impl<T,A> IntoIterator for Vec<T, A>.. donde un poco mas abajo vemos...
    type IntoIter = IntoIter<T, A>. No usamos A asi que usamos T que en nuestro caso es un vector
    de Ticket asi que seria:
    type IntoIter = IntoIter<Ticket>. Pero ese segundo IntoIter seria encontrado si estuviarmos
    dentro de la propia implementacion (impl) de Vector. Como estamos en la impl de TicketStore
    tenemos que poner toda la ruta, asi que quedaria como esta puesto abajo*/
    type IntoIter = std::vec::IntoIter<Ticket>; //herramienta que lleva la cuenta por donde va de la iteracion
    fn into_iter(self) -> Self::IntoIter{
        //let mut it = self.tickets.into_iter()
        //it. Podemos dejarlo en una linea:
        self.tickets.into_iter()
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use ticket_fields::test_helpers::{ticket_description, ticket_title};

    #[test]
    fn add_ticket() {
        let mut store = TicketStore::new();

        let ticket = Ticket {
            title: ticket_title(),
            description: ticket_description(),
            status: Status::ToDo,
        };
        store.add_ticket(ticket);

        let ticket = Ticket {
            title: ticket_title(),
            description: ticket_description(),
            status: Status::InProgress,
        };
        store.add_ticket(ticket);

        let tickets: Vec<_> = store.clone().into_iter().collect();
        assert_eq!(tickets, store.tickets);
    }
}
