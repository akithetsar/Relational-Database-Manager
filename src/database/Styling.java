package database;

import org.fxmisc.richtext.CodeArea;
import org.fxmisc.richtext.LineNumberFactory;
import org.fxmisc.richtext.model.StyleSpans;
import org.fxmisc.richtext.model.StyleSpansBuilder;

import java.util.Collection;
import java.util.Collections;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Styling {
    public static final String[] KEYWORDS = {
            "CREATE",
            "DROP",
            "SELECT",
            "FROM",
            "WHERE",
            "AND",
            "INSERT",
            "VALUES",
            "UPDATE",
            "SET",
            "DELETE",
            "SHOW",
            "TABLE",
            "FROM",
            "TABLES",
            "INTO"
    };
    public static StyleSpans<Collection<String>> computeHighlighting(String text) {
        Matcher matcher = Pattern.compile("\\b(" + String.join("|", KEYWORDS) + ")\\b").matcher(text);
        StyleSpansBuilder<Collection<String>> spansBuilder = new StyleSpansBuilder<>();
        int lastIdx = 0;
        while (matcher.find()) {
            spansBuilder.add(Collections.emptyList(), matcher.start() - lastIdx);
            spansBuilder.add(Collections.singleton("keyword"), matcher.end() - matcher.start());
            lastIdx = matcher.end();
        }
        spansBuilder.add(Collections.emptyList(), text.length() - lastIdx);
        return spansBuilder.create();
    }

    public static void codeAreaInit(CodeArea codeArea){
        codeArea.setParagraphGraphicFactory(LineNumberFactory.get(codeArea));
        codeArea.textProperty().addListener((obs, oldText, newText) -> {
            codeArea.setStyleSpans(0, Styling.computeHighlighting(newText));
        });
    }
}
