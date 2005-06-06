<?xml version="1.0" encoding="windows-1251"?> 
<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:import href="/usr/share/sgml/docbook/xsl-stylesheets/xhtml/chunk.xsl"/>
<xsl:param name="chunker.output.encoding" select="'koi8-r'"/>
<xsl:param name="use.id.as.filename" select="1"/>
<!--<xsl:param name="chunk.first.section" select="1"/>-->

<xsl:param name="section.autolabel" select="1"/>
<xsl:param name="label.from.part" select="1"/>
<xsl:param name="section.label.includes.component.label" select="1"/>

</xsl:stylesheet>