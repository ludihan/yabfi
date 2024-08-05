use std::{
    env, fs,
    io::{IsTerminal, Read},
    process::ExitCode,
};

mod brainfuck;

fn main() -> ExitCode {
    let mut stdin = std::io::stdin();
    let mut bf = brainfuck::Brainfuck::new();

    let is_pipe = !stdin.is_terminal();
    let input = &mut vec![];

    if !is_pipe {
        for argument in env::args().skip(1) {
            match fs::File::open(argument) {
                Ok(mut file) => {
                    if let Ok(_) = file.read_to_end(input) {
                        bf.interpret(input)
                    } else {
                        return ExitCode::from(1);
                    }
                }
                Err(_) => return ExitCode::from(1),
            }
        }
        ExitCode::from(0)
    } else {
        return match stdin.read_to_end(input) {
            Ok(_) => {
                bf.interpret(input);
                ExitCode::from(0)
            }

            Err(_) => ExitCode::from(1),
        };
    }
}
