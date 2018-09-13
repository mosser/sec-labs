import io.github.mosser.arduinoml.ens.compiler.*;
import io.github.mosser.arduinoml.ens.generator.*;
import io.github.mosser.arduinoml.ens.model.App;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTreeWalker;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import io.github.mosser.arduinoml.external.*;

public class Main {


    // mvn -q exec:java -Dexec.args="src/main/resources/led.arduinoml"
    public static void main (String[] args) throws Exception {
        System.out.println("\n\nRunning the ANTLR compiler for ArduinoML");

        CharStream stream = getCharStream(args);
        App theApp = buildModel(stream);
        exportToCode(theApp);

    }

    private static App buildModel(CharStream stream) {
        ArduinoMLLexer    lexer   = new ArduinoMLLexer(stream);
        lexer.removeErrorListeners();
        lexer.addErrorListener(new StopErrorListener());

        ArduinoMLParser   parser  = new ArduinoMLParser(new CommonTokenStream(lexer));
        parser.removeErrorListeners();
        parser.addErrorListener(new StopErrorListener());

        ParseTreeWalker walker  = new ParseTreeWalker();
        ModelBuilder      builder = new ModelBuilder();

        walker.walk(builder, parser.app()); // parser.app() is the entry point of the grammar

        return builder.retrieve();
    }

    private static void exportToCode(App theApp) {

        Visitor codeGenerator = new ToC();
        theApp.accept(codeGenerator);
        try {
            System.out.println("Generating C code: ./output/fsm.h");
            Files.write(Paths.get("./output/fsm.h"), codeGenerator.getHeaders().toString().getBytes());
            System.out.println("Generating C code: ./output/main.c");
            Files.write(Paths.get("./output/main.c"), codeGenerator.getCode().toString().getBytes());
            System.out.println("Code generation: done");
            System.out.println("Board upload : cd output && make upload && cd ..;");
        } catch (IOException e) {
            System.err.println(e);
        }
    }

    private static CharStream getCharStream(String[] args) throws IOException {
        if (args.length < 1)
            throw new RuntimeException("no input file");
        Path input = Paths.get(new File(args[0]).toURI());
        System.out.println("Using input file: " + input);
        return CharStreams.fromPath(input);
    }

}
