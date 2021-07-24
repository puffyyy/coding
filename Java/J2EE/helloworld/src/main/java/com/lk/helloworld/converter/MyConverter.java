package com.lk.helloworld.converter;

import com.lk.helloworld.entity.Book;
import org.springframework.http.HttpInputMessage;
import org.springframework.http.HttpOutputMessage;
import org.springframework.http.MediaType;
import org.springframework.http.converter.HttpMessageConverter;
import org.springframework.http.converter.HttpMessageNotReadableException;
import org.springframework.http.converter.HttpMessageNotWritableException;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.List;

public class MyConverter implements HttpMessageConverter<Book> {
    @Override
    public boolean canRead(Class aClass, MediaType mediaType) {
        return false;
    }
    
    @Override
    public boolean canWrite(Class aClass, MediaType mediaType) {
        return aClass.isAssignableFrom(Book.class);
    }
    
    @Override
    public List<MediaType> getSupportedMediaTypes() {
        return MediaType.parseMediaTypes("application/book");
    }
    
    @Override
    public List<MediaType> getSupportedMediaTypes(Class<?> clazz) {
        return MediaType.parseMediaTypes("application/book");
    }
    
    @Override
    public void write(Book book, MediaType mediaType, HttpOutputMessage httpOutputMessage) throws IOException, HttpMessageNotWritableException {
        String data = book.getName()+";"+book.getAuthor()+";"+book.getPublicationDate();
        httpOutputMessage.getBody().write(data.getBytes(StandardCharsets.UTF_8));
    }
    
    @Override
    public Book read(Class aClass, HttpInputMessage httpInputMessage) throws IOException, HttpMessageNotReadableException {
        return null;
    }
    
}
