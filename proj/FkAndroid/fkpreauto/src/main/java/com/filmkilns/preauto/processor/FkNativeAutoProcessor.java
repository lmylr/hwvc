package com.filmkilns.preauto.processor;

import com.filmkilns.annotation.FkNativeAuto;
import com.google.auto.service.AutoService;
import com.google.common.collect.ImmutableSet;

import org.apache.velocity.Template;
import org.apache.velocity.VelocityContext;
import org.apache.velocity.app.VelocityEngine;
import org.apache.velocity.runtime.RuntimeConstants;
import org.apache.velocity.util.introspection.UberspectImpl;
import org.apache.velocity.util.introspection.UberspectPublicFields;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import javax.annotation.processing.ProcessingEnvironment;
import javax.annotation.processing.Processor;
import javax.annotation.processing.RoundEnvironment;
import javax.lang.model.element.Element;
import javax.lang.model.element.ElementKind;
import javax.lang.model.element.TypeElement;
import com.sun.tools.javac.code.Symbol;
import com.sun.tools.javac.code.Type;

@AutoService(Processor.class)
public class FkNativeAutoProcessor extends FkAbsProcessor {
    private final static String TAG = "FkNativeAutoProcessor";
    private final static Class[] SIG_MAP_ID = {boolean.class, byte.class, char.class, short.class, int.class, long.class, float.class, double.class, void.class, String.class, Object.class};
    private final static String[] SIG_MAP_V = {"Z", "B", "C", "S", "I", "J", "F", "D", "V", "Ljava/lang/String;", "Ljava/lang/Object;"};
    private VelocityEngine engine;

    private static class CreationItem {
        String name;
        String path;

        @Override
        public String toString() {
            return "CreationItem{" +
                    "name='" + name + '\'' +
                    ", path='" + path + '\'' +
                    '}';
        }
    }

    @Override
    public synchronized void init(ProcessingEnvironment processingEnvironment) {
        super.init(processingEnvironment);
        logI(TAG, "init: projectDir=" + getProjectDir() + ", mainDir=" + getSourceMainDir());
        engine = new VelocityEngine();
        engine.setProperty(RuntimeConstants.FILE_RESOURCE_LOADER_PATH, new File("/Volumes/FXS790_HD/Documents/Projects/AndroidStudioProjects/FilmKilns/proj/FkAndroid", "fkpreauto/src/main/resources/").getAbsolutePath());
        engine.setProperty(RuntimeConstants.UBERSPECT_CLASSNAME, UberspectImpl.class.getName() + ", " + UberspectPublicFields.class.getName());
        engine.init();
    }

    private String getSimpleClassName(Symbol.ClassSymbol symbol) {
        String name = symbol.className();
        return name.substring(name.lastIndexOf(".") + 1);
    }

    private List<CreationItem> getCreationItems(RoundEnvironment env) {
        Set<? extends Element> elements = env.getElementsAnnotatedWith(FkNativeAuto.class);
        List<CreationItem> items = new ArrayList<>();
        for (Element e : elements) {
            if (e.getKind() == ElementKind.CLASS) {
                Symbol.ClassSymbol symbol = (Symbol.ClassSymbol) e;
                FkNativeAuto ann = symbol.getAnnotation(FkNativeAuto.class);
                CreationItem creation = new CreationItem();
                creation.name = getSimpleClassName(symbol);
                creation.path = ann.path();
                items.add(creation);
            }
        }
        return items;
    }

    private void generate(CreationItem item) {
        String dirStr = getSourceMainDir() + "/" + item.path;
        File dir = new File(dirStr);
        if (!dir.exists()) {
            dir.mkdirs();
        }
//        generateHeader(new File(dir,  item.name + ".h"));
    }

    private Template createTemplate(String tempName) {
        return engine.getTemplate(tempName);
    }

    private void generateHeader(File file) {
        if (file.exists()) {
            file.delete();
        }
        VelocityContext ctx = new VelocityContext();
//        ctx.put("classPackage", classPackage);
//        ctx.put("$className", $className);
        try {
            FileWriter writer = new FileWriter(file);
            Template template = createTemplate("FkNativeInterface.temp");
            template.merge(ctx, writer);
            writer.flush();
            writer.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private void generateCPP() {

    }

    @Override
    public boolean process(Set<? extends TypeElement> set, RoundEnvironment env) {
        logI(TAG, "process");
        List<CreationItem> items = getCreationItems(env);
        logI(TAG, "items: " + items);
        for (CreationItem it : items) {
            generate(it);
        }
        return false;
    }

    @Override
    public Set<String> getSupportedAnnotationTypes() {
        return ImmutableSet.of(FkNativeAuto.class.getCanonicalName());
    }
}
