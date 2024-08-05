use std::{io::Read, num::Wrapping};

pub struct Brainfuck {
    cursor: usize,
    cells: Vec<Wrapping<u8>>,
    wrap_cell: bool,
    wrap_cursor: bool,
}

const NUM_CELLS: usize = 30000;

impl Brainfuck {
    pub fn new() -> Self {
        Self {
            ..Default::default()
        }
    }

    pub fn interpret(&mut self, input: &[u8]) {
        let mut loop_points: Vec<usize> = Vec::new();
        let mut position: usize = 0;

        while position < input.len() {
            match input[position] {
                b'+' => {
                    self.cells[self.cursor] += 1;
                }
                b'-' => {
                    self.cells[self.cursor] -= 1;
                }
                b'>' => {
                    if self.cursor == NUM_CELLS - 1 {
                        self.cursor = 0;
                    } else {
                        self.cursor += 1;
                    }
                }
                b'<' => {
                    if self.cursor == 0 {
                        self.cursor = NUM_CELLS - 1;
                    } else {
                        self.cursor -= 1;
                    }
                }
                b',' => {
                    let mut byte = [0_u8];
                    std::io::stdin().read_exact(&mut byte).unwrap();
                }
                b'.' => {
                    print!("{}", self.cells[self.cursor].0 as char);
                }
                b'[' => loop_points.push(position),
                b']' => {
                    if let Some(jump) = loop_points.pop() {
                        if self.cells[self.cursor].0 == 0 {
                            position = jump;
                        }
                    }
                }
                _ => {}
            }
            position += 1
        }
    }
}

impl Default for Brainfuck {
    fn default() -> Self {
        Self {
            cursor: 0,
            cells: vec![Wrapping(0); 30000],
            wrap_cell: true,
            wrap_cursor: true,
        }
    }
}
