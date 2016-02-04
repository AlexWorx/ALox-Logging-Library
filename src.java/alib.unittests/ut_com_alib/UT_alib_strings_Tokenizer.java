// #################################################################################################
//  Unit Tests - AWorx Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package ut_com_alib;
import org.junit.Test;

import ut_com_aworx_uttools.UnitTest;
import ut_com_aworx_uttools.UnitTestSampleWriter;

import com.aworx.lib.enums.Whitespaces;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.Substring;
import com.aworx.lib.strings.Tokenizer;


public class UT_alib_strings_Tokenizer extends UnitTest
{

//##################################################################################################
// SAMPLE code of class documentation
//##################################################################################################

void documentationSampleTokenizer()
{
    UnitTestSampleWriter utsw= new UnitTestSampleWriter("DOC_SAMPLES_ALIB_LIB_STRING_TOKEN.txt");

//! [DOC_SAMPLES_ALIB_LIB_STRING_TOKEN]
    // data string to tokenize
    AString data= new AString( "test;  abc ; 1,2 , 3 ; xyz ; including;separator" );

    // create tokenizer on data with ';' as delimiter
    Tokenizer tokens= new Tokenizer( data, ';' );

    // read tokens
    System.out.println( tokens.next().toString() ); // will print "test"
    System.out.println( tokens.next().toString() ); // will print "abc"
    System.out.println( tokens.next().toString() ); // will print "1,2 , 3"

    // tokenize actual (third) token (nested tokenizer)
    Tokenizer subTokens= new Tokenizer( tokens.actual,  ',');
    System.out.print( subTokens.next().toString() );

    while( subTokens.hasNext() )
        System.out.print( "~" + subTokens.next().toString() );

    System.out.println();

    // continue with the main tokenizer
    System.out.println( tokens.next().toString() ); // will print "xyz"

    // grab the rest, as we know that the last token might include our separator character
    System.out.println( tokens.getRest().toString() ); // will print "including;separator"
//! [DOC_SAMPLES_ALIB_LIB_STRING_TOKEN]

    utsw.flushAndResetSystemOut();
}

    
    @SuppressWarnings("static-method")
    @Test
    public void DocumentationSamples()
    {
    
        //UT_PRINT("*** Documentation Sample +**")
        documentationSampleTokenizer();
    }
    

    void tokenizerTest( String inputString, AString res, char delim, char newDelim,
                        Whitespaces trim, int inpStart, int inpEnd  )
    {
        Substring inp= new Substring( inputString );
        if ( inpStart >= 0 ) inp.start= inpStart;
        if ( inpEnd   >= 0 ) inp.end=   inpEnd;
        res.clear();

        Tokenizer tok= new Tokenizer( inp, delim );

        while( tok.hasNext() )
        {
            tok.next(trim).copyTo( res, true );
            res._( newDelim );
        }

    }

    void tokenizerTest( String inputString, AString res, char delim, char newDelim,
                        Whitespaces trim, int inpStart  )
    {
        tokenizerTest( inputString, res, delim, newDelim, trim, inpStart, -1);
    }

    void tokenizerTest( String inputString, AString res, char delim, char newDelim,
                        Whitespaces trim )
    {
        tokenizerTest( inputString, res, delim, newDelim, trim, -1, -1);
    }

    @SuppressWarnings("static-method")
    @Test
    public void Tokenize()
    {
        AString astr=  new AString();
        AString res=   new AString();

        // tokenizing empty string
        astr.clear()._( "" );
        res.clear();
        {
            Tokenizer tok= new Tokenizer( astr, ',' );   UT_EQ( true,  tok.hasNext() );
            tok.next().copyTo( res, true );              UT_EQ( "", res );
        }

        // tokenizing no delim
        astr.clear()._( "abc" );
        res.clear();
        {
            Tokenizer tok= new Tokenizer( astr, ',' );                UT_EQ( true,  tok.hasNext() );
            tok.next().copyTo( res, true );     UT_EQ( "abc", res );
        }

        // tokenizing
        {
            tokenizerTest( "abc",                res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "abc@",               res );
            tokenizerTest( "a,bc",               res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "a@bc@",              res );
            tokenizerTest( "a,bc",               res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "a@bc@",              res );
            tokenizerTest( ",",                  res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "@@",                 res );
            tokenizerTest( ",,",                 res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "@@@",                res );
            tokenizerTest( "a,b,c,,",            res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "a@b@c@@@",           res );
            tokenizerTest( "a,b,c",              res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "a@b@c@",             res );
            tokenizerTest( ",a,b,c",             res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "@a@b@c@",            res );
            tokenizerTest( "123567",             res, ',', '@',   Whitespaces.TRIM,  2,    2 );  UT_EQ ( "3@",                 res );
            tokenizerTest( "123567",             res, ',', '@',   Whitespaces.TRIM,  2,    1 );  UT_EQ ( "@",                  res );
            tokenizerTest( "  abc , def , ghe ", res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "abc@def@ghe@",       res );
            tokenizerTest( "abc , def,ghe,",     res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "abc@def@ghe@@",      res );
            tokenizerTest( "  abc , def , ghe ", res, ',', '@',   Whitespaces.KEEP,-1,   -1 );  UT_EQ ( "  abc @ def @ ghe @",res );
            tokenizerTest( "abc , def,ghe,",     res, ',', '@',   Whitespaces.KEEP,-1,   -1 );  UT_EQ ( "abc @ def@ghe@@",    res );
        }

        // tokenizing with different delimiters
        {
            astr.clear()._( "1,5;3@4" );
            Tokenizer tok= new Tokenizer(astr, ',');
            tok.next()                       .copyTo( res );    UT_EQ ( "1",   res );  UT_EQ( true,  tok.hasNext() );
            tok.next( Whitespaces.TRIM, ';' ).copyTo( res );    UT_EQ ( "5",   res );  UT_EQ( true,  tok.hasNext() );
            tok.next( Whitespaces.TRIM, '@' ).copyTo( res );    UT_EQ ( "3",   res );  UT_EQ( true,  tok.hasNext() );
            tok.next( Whitespaces.TRIM, '-' ).copyTo( res );    UT_EQ ( "4",   res );  UT_EQ( false, tok.hasNext() );
        }

        // tokenizing with different delimiters
        {
            astr.clear()._( "abc, 5;\t3;;; 4  " );
            Tokenizer tok= new Tokenizer(astr,',');
            tok.next()                       .copyTo( res );    UT_EQ ( "abc", res );  UT_EQ( true,  tok.hasNext() );
            tok.next( Whitespaces.TRIM, ';' ).copyTo( res );    UT_EQ ( "5",   res );  UT_EQ( true,  tok.hasNext() );
            tok.next()                       .copyTo( res );    UT_EQ ( "3",   res );  UT_EQ( true,  tok.hasNext() );
            tok.next()                        .copyTo( res );    UT_EQ ( "",    res );  UT_EQ( true,  tok.hasNext() );
            tok.getRest()                    .copyTo( res );    UT_EQ ( "; 4", res );  UT_EQ( false, tok.hasNext() );
        }

        // sub-tokens
        {
            astr.clear()._( "1,2;3 , 4;5,;," );
            Tokenizer tok= new Tokenizer(astr, ';');

            Tokenizer tok2= new Tokenizer( tok.next(), ',');
            tok2.next().copyTo( res ); UT_EQ ( "1", res );  UT_TRUE(  tok2.hasNext() );
            tok2.next().copyTo( res ); UT_EQ ( "2", res );  UT_TRUE( !tok2.hasNext() );
            UT_TRUE( tok.hasNext() );

            tok2.set( tok.next(), ',');
            tok2.next().copyTo( res ); UT_EQ ( "3", res );  UT_TRUE(  tok2.hasNext() );
            tok2.next().copyTo( res ); UT_EQ ( "4", res );  UT_TRUE( !tok2.hasNext() );
            UT_TRUE( tok.hasNext() );

            tok2.set( tok.next(), ',');
            tok2.next().copyTo( res ); UT_EQ ( "5", res );  UT_TRUE(  tok2.hasNext() );
            tok2.next().copyTo( res ); UT_EQ ( "",  res );  UT_TRUE( !tok2.hasNext() );
            UT_TRUE( tok.hasNext() );

            tok2.set( tok.next(), ',');
            tok2.next().copyTo( res ); UT_EQ ( "", res );  UT_TRUE(  tok2.hasNext() );
            tok2.next().copyTo( res ); UT_EQ ( "", res );  UT_TRUE( !tok2.hasNext() );
            UT_TRUE( !tok.hasNext() );
        }

    }

}
