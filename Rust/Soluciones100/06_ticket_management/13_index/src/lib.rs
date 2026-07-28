// TODO: Implement `Index<&TicketId>` and `Index<TicketId>` for `TicketStore`.

use ticket_fields::{TicketDescription, TicketTitle};
use std::ops::Index;

#[derive(Clone)]
pub struct TicketStore {
    tickets: Vec<Ticket>,
    counter: u64,
}

#[derive(Clone, Copy, Debug, PartialEq)]
pub struct TicketId(u64);

#[derive(Clone, Debug, PartialEq)]
pub struct Ticket {
    pub id: TicketId,
    pub title: TicketTitle,
    pub description: TicketDescription,
    pub status: Status,
}

#[derive(Clone, Debug, PartialEq)]
pub struct TicketDraft {
    pub title: TicketTitle,
    pub description: TicketDescription,
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
            counter: 0,
        }
    }

    pub fn add_ticket(&mut self, ticket: TicketDraft) -> TicketId {
        let id = TicketId(self.counter);
        self.counter += 1;
        let ticket = Ticket {
            id,
            title: ticket.title,
            description: ticket.description,
            status: Status::ToDo,
        };
        self.tickets.push(ticket);
        id
    }

    pub fn get(&self, id: TicketId) -> Option<&Ticket> {
        self.tickets.iter().find(|&t| t.id == id)
    }
}

   //indexes
   /*En ambos devolvemos un &Ticket por que? Pues otra vez por el ownership. Si el vector fuera de i32, en ellos va asociado el COPY y por lo tanto
   al devolver el vector[indice] se hace una copia. PERO AQUI NO HAY COPY asi que al hacer un tickets[indice] se tendría que sacar dicho elemento del vector
   ya que no está implementada la COPY, y por lo tanto quedaría un vector vacio de ese elemento (valor basura), y eso es IMPOSIBLE en Rust. Asi que lo suyo es
   devolverlo por referencia apuntando a su dirección de memoria.
   Luego si quisieramos acceder a un elemento de dicho ticket1 (como en el test), valdria poner ticket1.title y no hace falta (*ticket1).title por que Rust hace
   directamente una dereferenciación automática cuando viene por referencia. En C recordemos que seria ticket1->title*/
    impl Index<TicketId> for TicketStore{
        type Output = Ticket;
        fn index(&self, index: TicketId) -> &Self::Output{
            &self.tickets[index.0 as usize]
        }
    }

    impl Index<&TicketId> for TicketStore{
        type Output = Ticket;
        fn index(&self, index: &TicketId) -> &Self::Output{
           &self.tickets[index.0 as usize]
        }
    }



#[cfg(test)]
mod tests {
    use crate::{Status, TicketDraft, TicketStore};
    use ticket_fields::test_helpers::{ticket_description, ticket_title};

    #[test]
    fn works() {
        let mut store = TicketStore::new();

        let draft1 = TicketDraft {
            title: ticket_title(),
            description: ticket_description(),
        };
        let id1 = store.add_ticket(draft1.clone());
        let ticket1 = &store[id1];
        assert_eq!(draft1.title, ticket1.title);
        assert_eq!(draft1.description, ticket1.description);
        assert_eq!(ticket1.status, Status::ToDo);

        let draft2 = TicketDraft {
            title: ticket_title(),
            description: ticket_description(),
        };
        let id2 = store.add_ticket(draft2);
        let ticket2 = &store[&id2];

        assert_ne!(id1, id2);
    }
}
